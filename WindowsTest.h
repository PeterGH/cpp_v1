#ifndef _WINDOWSTEST_H_
#define _WINDOWSTEST_H_

#include "Test.h"
#include <io.h>

using namespace Test;

namespace Test {
namespace Windows {
class Path {
  private:
    wchar_t drive[_MAX_DRIVE];
    wchar_t directory[_MAX_DIR];
    wchar_t file[_MAX_FNAME];
    wchar_t extension[_MAX_EXT];

  public:
    Path(const wchar_t *path) {
        _wsplitpath_s(path, drive, _MAX_DRIVE, directory, _MAX_DIR, file,
                      _MAX_FNAME, extension, _MAX_EXT);
    }

    ~Path(void) {}
    wstring FullPath(void) const {
        wchar_t path[_MAX_PATH];
        _wmakepath_s(path, _MAX_PATH, drive, directory, file, extension);
        return wstring(path);
    }

    wstring Drive(void) const { return wstring(drive); }
    wstring Directory(void) const { return wstring(directory); }
    wstring File(void) const { return wstring(file); }
    wstring Extension(void) const { return wstring(extension); }

    static wchar_t *Combine(wchar_t *output, const wchar_t *parent,
                            const wchar_t *child) {
        wcscpy_s(output, _MAX_PATH, parent);
        if (output[wcslen(output) - 1] != L'\\') {
            wcscat_s(output, _MAX_PATH, L"\\");
        }
        wcscat_s(output, _MAX_PATH, child);
        return output;
    }

    static wchar_t *Combine(wchar_t *parent, const wchar_t *child) {
        if (parent[wcslen(parent) - 1] != L'\\') {
            wcscat_s(parent, _MAX_PATH, L"\\");
        }
        wcscat_s(parent, _MAX_PATH, child);
        return parent;
    }

    static vector<wstring> &GetItems(vector<wstring> &items,
                                     const wstring &directory,
                                     function<bool(struct _wfinddata_t &)> skip,
                                     const wstring &wildchar = L"*",
                                     const bool recursive = false) {
        wchar_t path[_MAX_PATH];
        Combine(path, directory.c_str(), wildchar.c_str());

        struct _wfinddata_t item;
        intptr_t hItem;
        hItem = _wfindfirst(path, &item);

        if (hItem != -1L) {
            do {
                if (skip(item))
                    continue;
                Combine(path, directory.c_str(), item.name);
                items.push_back(wstring(path));
            } while (_wfindnext(hItem, &item) == 0);

            _findclose(hItem);
        }

        if (recursive) {
            vector<wstring> subdirs;
            GetDirectories(subdirs, directory);
            for (vector<wstring>::iterator it = subdirs.begin();
                 it != subdirs.end(); it++) {
                GetItems(items, it->data(), skip, wildchar, recursive);
            }
        }
        return items;
    }

    static concurrent_vector<wstring> &
    GetItemsP(concurrent_vector<wstring> &items, const wstring &directory,
              function<bool(struct _wfinddata_t &)> skip,
              const wstring &wildchar = L"*", const bool recursive = false) {
        wchar_t path[_MAX_PATH];
        Combine(path, directory.c_str(), wildchar.c_str());

        struct _wfinddata_t item;
        intptr_t hItem;
        hItem = _wfindfirst(path, &item);

        if (hItem != -1L) {
            do {
                if (skip(item))
                    continue;
                Combine(path, directory.c_str(), item.name);
                items.push_back(wstring(path));
            } while (_wfindnext(hItem, &item) == 0);

            _findclose(hItem);
        }

        if (recursive) {
            vector<wstring> subdirs;
            GetDirectories(subdirs, directory);
            // for_each(subdirs.begin(), subdirs.end(), [](wstring dir) {
            // wprintf_s(L"  %s:\n", dir); }); for (vector<wstring>::iterator it
            // = subdirs.begin(); it != subdirs.end(); it ++) { 	wprintf_s(L"
            //%s:\n", it->data());
            //}
            parallel_for_each(
                subdirs.begin(), subdirs.end(),
                [&items, &skip, &wildchar, recursive](wstring &dir) {
                    GetItemsP(items, dir, skip, wildchar, recursive);
                });
        }
        return items;
    }

    static vector<wstring> &GetDirectories(vector<wstring> &items,
                                           const wstring &directory,
                                           const wstring &wildchar = L"*",
                                           const bool recursive = false) {
        return GetItems(
            items, directory,
            [](struct _wfinddata_t &item) -> bool {
                return wcscmp(item.name, L".") == 0 ||
                       wcscmp(item.name, L"..") == 0 ||
                       (item.attrib & _A_SUBDIR) == 0;
            },
            wildchar, recursive);
    }

    static concurrent_vector<wstring> &
    GetDirectories(concurrent_vector<wstring> &items, const wstring &directory,
                   const wstring &wildchar = L"*",
                   const bool recursive = false) {
        return GetItemsP(
            items, directory,
            [](struct _wfinddata_t &item) -> bool {
                return wcscmp(item.name, L".") == 0 ||
                       wcscmp(item.name, L"..") == 0 ||
                       (item.attrib & _A_SUBDIR) == 0;
            },
            wildchar, recursive);
    }

    static vector<wstring> &GetFiles(vector<wstring> &items,
                                     const wstring &directory,
                                     const wstring &wildchar = L"*",
                                     const bool recursive = false) {
        // Valid attributes are:
        // _A_NORMAL	0x00
        // _A_RDONLY	0x01
        // _A_HIDDEN	0x02
        // _A_SYSTEM	0x04
        // _A_SUBDIR	0x10
        // _A_ARCH		0x20
        return GetItems(
            items, directory,
            [](struct _wfinddata_t &item) -> bool {
                return (item.attrib & _A_SUBDIR) != 0;
            },
            wildchar, recursive);
    }

    static concurrent_vector<wstring> &
    GetFiles(concurrent_vector<wstring> &items, const wstring &directory,
             const wstring &wildchar = L"*", const bool recursive = false) {
        // Valid attributes are:
        // _A_NORMAL	0x00
        // _A_RDONLY	0x01
        // _A_HIDDEN	0x02
        // _A_SYSTEM	0x04
        // _A_SUBDIR	0x10
        // _A_ARCH		0x20
        return GetItemsP(
            items, directory,
            [](struct _wfinddata_t &item) -> bool {
                return (item.attrib & _A_SUBDIR) != 0;
            },
            wildchar, recursive);
    }

    static void ProcessItems(const wstring &directory,
                             function<bool(struct _wfinddata_t &)> skip,
                             function<void(wstring)> process,
                             const wstring &wildchar = L"*",
                             const bool recursive = false) {
        wchar_t path[_MAX_PATH];
        Combine(path, directory.c_str(), wildchar.c_str());

        struct _wfinddata_t item;
        intptr_t hItem;
        hItem = _wfindfirst(path, &item);

        if (hItem != -1L) {
            do {
                if (skip(item))
                    continue;
                Combine(path, directory.c_str(), item.name);
                process(wstring(path));
            } while (_wfindnext(hItem, &item) == 0);

            _findclose(hItem);
        }

        if (recursive) {
            vector<wstring> subdirs;
            GetDirectories(subdirs, directory);
            // for_each(subdirs.begin(), subdirs.end(), [](wstring dir) {
            // wprintf_s(L"  %s:\n", dir); });
            parallel_for_each(
                subdirs.begin(), subdirs.end(),
                [&skip, &process, &wildchar, recursive](wstring &dir) {
                    ProcessItems(dir, skip, process, wildchar, recursive);
                });
        }
    }

    static void ProcessDirectories(const wstring &directory,
                                   function<void(wstring)> process,
                                   const wstring &wildchar = L"*",
                                   const bool recursive = false) {
        ProcessItems(
            directory,
            [](struct _wfinddata_t &item) -> bool {
                return wcscmp(item.name, L".") == 0 ||
                       wcscmp(item.name, L"..") == 0 ||
                       (item.attrib & _A_SUBDIR) == 0;
            },
            process, wildchar, recursive);
    }

    static void ProcessFiles(const wstring &directory,
                             function<void(wstring)> process,
                             const wstring &wildchar = L"*",
                             const bool recursive = false) {
        // Valid attributes are:
        // _A_NORMAL	0x00
        // _A_RDONLY	0x01
        // _A_HIDDEN	0x02
        // _A_SYSTEM	0x04
        // _A_SUBDIR	0x10
        // _A_ARCH		0x20
        ProcessItems(
            directory,
            [](struct _wfinddata_t &item) -> bool {
                return (item.attrib & _A_SUBDIR) != 0;
            },
            process, wildchar, recursive);
    }
};
} // namespace Windows
} // namespace Test

class WindowsTest : public TestClass {
  public:
    WindowsTest(Log &log) : TestClass(log) {}
    ~WindowsTest(void) {}
    void Init(void);
};

void WindowsTest::Init(void) {
    Add("Path", [&]() {
        wchar_t buffer[_MAX_PATH];
        if (_wfullpath(buffer, L".", _MAX_PATH) == NULL) {
            return -1;
        }

        wstring path(buffer);
        wcout << path << endl;

        wstring wildchar(L"*");

        bool recursive = true;

        wcout << "GetItems" << endl;

        vector<wstring> items;
        Widnows::Path::GetDirectories(items, path, wildchar, recursive);
        Windows::Path::GetFiles(items, path, wildchar, recursive);

        for (vector<wstring>::iterator it = items.begin(); it != items.end();
             it++) {
            wcout << "  " << it->data() << endl;
        }

        wcout << "GetItemsP" << endl;

        concurrent_vector<wstring> itemsp;
        Windows::Path::GetDirectories(itemsp, path, wildchar, recursive);
        Windows::Path::GetFiles(itemsp, path, wildchar, recursive);

        for (concurrent_vector<wstring>::iterator it = itemsp.begin();
             it != itemsp.end(); it++) {
            wcout << "  " << it->data() << endl;
        }

        wcout << "GetItemsP: " << itemsp.size() << endl;

        wcout << "ProcessItems" << endl;

        auto p = [](wstring x) { wcout << "  " << x << endl; };

        Windows::Path::ProcessDirectories(path, p, wildchar, recursive);
        Windows::Path::ProcessFiles(path, p, wildchar, recursive);

        wcout << "GetItems: " << items.size() << endl;
        wcout << "GetItemsP: " << itemsp.size() << endl;
        return 0;
    });
}

#endif