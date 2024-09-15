#include <node.h>
#include <v8.h>
#include <windows.h>
#include <string>
#include <iostream>

using namespace v8;

#ifndef COMPRESSION_FORMAT_NONE
#define COMPRESSION_FORMAT_NONE 0x0000
#endif

#ifndef COMPRESSION_FORMAT_LZNT1
#define COMPRESSION_FORMAT_LZNT1 0x0002
#endif

void SetFileAttributes(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();

  if (args.Length() < 2 || !args[0]->IsString() || !args[1]->IsString()) {
    isolate->ThrowException(Exception::TypeError(
        String::NewFromUtf8(isolate, "Invalid arguments").ToLocalChecked()));
    return;
  }

  String::Utf8Value filePath(isolate, args[0]);
  std::string path(*filePath);
  std::string mode(*String::Utf8Value(isolate, args[1]));

  DWORD attributes = GetFileAttributesA(path.c_str());
  if (attributes == INVALID_FILE_ATTRIBUTES) {
    isolate->ThrowException(Exception::Error(
        String::NewFromUtf8(isolate, "Failed to get file attributes").ToLocalChecked()));
    return;
  }

  if (mode == "hide") {
    attributes |= FILE_ATTRIBUTE_HIDDEN;
  } else if (mode == "show") {
    attributes &= ~FILE_ATTRIBUTE_HIDDEN;
  }

  else if (mode == "system") {
    attributes |= FILE_ATTRIBUTE_SYSTEM;
  } else if (mode == "nosystem") {
    attributes &= ~FILE_ATTRIBUTE_SYSTEM;
  }

  else if (mode == "readonly") {
    attributes |= FILE_ATTRIBUTE_READONLY;
  } else if (mode == "writable") {
    attributes &= ~FILE_ATTRIBUTE_READONLY;
  }

  else if (mode == "archive") {
    attributes |= FILE_ATTRIBUTE_ARCHIVE;
  } else if (mode == "noarchive") {
    attributes &= ~FILE_ATTRIBUTE_ARCHIVE;
  }

  else if (mode == "temporary") {
    attributes |= FILE_ATTRIBUTE_TEMPORARY;
  } else if (mode == "notemporary") {
    attributes &= ~FILE_ATTRIBUTE_TEMPORARY;
  }

  else if (mode == "normal") {
    attributes = FILE_ATTRIBUTE_NORMAL;
  }

  else if (mode == "compress" || mode == "nocompress") {
    HANDLE hFile = CreateFileA(
        path.c_str(), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);

    if (hFile == INVALID_HANDLE_VALUE) {
      isolate->ThrowException(Exception::Error(
          String::NewFromUtf8(isolate, "Failed to open file").ToLocalChecked()));
      return;
    }

    USHORT compressionState;
    if (mode == "compress") {
      compressionState = COMPRESSION_FORMAT_LZNT1;
    } else {
      compressionState = COMPRESSION_FORMAT_NONE;
    }

    DWORD bytesReturned;
    BOOL result = DeviceIoControl(
        hFile, FSCTL_SET_COMPRESSION, &compressionState, sizeof(compressionState),
        NULL, 0, &bytesReturned, NULL);

    CloseHandle(hFile);

    if (!result) {
      isolate->ThrowException(Exception::Error(
          String::NewFromUtf8(isolate, "Failed to set compression state").ToLocalChecked()));
      return;
    }

    args.GetReturnValue().Set(True(isolate));
    return;
  }

  else if (mode == "not_indexed") {
    attributes |= FILE_ATTRIBUTE_NOT_CONTENT_INDEXED;
  } else if (mode == "indexed") {
    attributes &= ~FILE_ATTRIBUTE_NOT_CONTENT_INDEXED;
  }

  BOOL result = SetFileAttributesA(path.c_str(), attributes);
  
  if (result) {
    args.GetReturnValue().Set(True(isolate));
  } else {
    isolate->ThrowException(Exception::Error(
        String::NewFromUtf8(isolate, "Failed to set file attributes").ToLocalChecked()));
  }
}

void GetFileAttributes(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();

  if (args.Length() < 1 || !args[0]->IsString()) {
    isolate->ThrowException(Exception::TypeError(
        String::NewFromUtf8(isolate, "Invalid arguments").ToLocalChecked()));
    return;
  }

  String::Utf8Value filePath(isolate, args[0]);
  std::string path(*filePath);

  DWORD attributes = GetFileAttributesA(path.c_str());
  if (attributes == INVALID_FILE_ATTRIBUTES) {
    isolate->ThrowException(Exception::Error(
        String::NewFromUtf8(isolate, "Failed to get file attributes").ToLocalChecked()));
    return;
  }

  Local<Object> result = Object::New(isolate);

  result->Set(isolate->GetCurrentContext(),
              String::NewFromUtf8(isolate, "hidden").ToLocalChecked(),
              Boolean::New(isolate, (attributes & FILE_ATTRIBUTE_HIDDEN) != 0)).FromJust();
  result->Set(isolate->GetCurrentContext(),
              String::NewFromUtf8(isolate, "system").ToLocalChecked(),
              Boolean::New(isolate, (attributes & FILE_ATTRIBUTE_SYSTEM) != 0)).FromJust();
  result->Set(isolate->GetCurrentContext(),
              String::NewFromUtf8(isolate, "readonly").ToLocalChecked(),
              Boolean::New(isolate, (attributes & FILE_ATTRIBUTE_READONLY) != 0)).FromJust();
  result->Set(isolate->GetCurrentContext(),
              String::NewFromUtf8(isolate, "archive").ToLocalChecked(),
              Boolean::New(isolate, (attributes & FILE_ATTRIBUTE_ARCHIVE) != 0)).FromJust();
  result->Set(isolate->GetCurrentContext(),
              String::NewFromUtf8(isolate, "temporary").ToLocalChecked(),
              Boolean::New(isolate, (attributes & FILE_ATTRIBUTE_TEMPORARY) != 0)).FromJust();
  result->Set(isolate->GetCurrentContext(),
              String::NewFromUtf8(isolate, "not_indexed").ToLocalChecked(),
              Boolean::New(isolate, (attributes & FILE_ATTRIBUTE_NOT_CONTENT_INDEXED) != 0)).FromJust();
  
  args.GetReturnValue().Set(result);
}

void Initialize(Local<Object> exports) {
  NODE_SET_METHOD(exports, "setFileAttributes", SetFileAttributes);
  NODE_SET_METHOD(exports, "getFileAttributes", GetFileAttributes);
}

NODE_MODULE(NODE_GYP_MODULE_NAME, Initialize)
