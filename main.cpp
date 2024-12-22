 #include <v8.h>

 using namespace v8; 

//  int main(int argc, char *argv[]) { 
// 	 // 创建一个句柄作用域 ( 在栈上 ) 
// 	 HandleScope handle_scope; 

// 	 // 创建一个新的上下文对象
// 	 Persistent<Context> context = Context::New(); 

// 	 // 进入上一步创建的上下文，用于编译执行 helloworld 
// 	 Context::Scope context_scope(context); 

// 	 // 创建一个字符串对象，值为'Hello, Wrold!', 字符串对象被 JS 引擎
// 	 // 求值后，结果为'Hello, World!'
// 	 Handle<String> source = String::New("'Hello' + ', World!'"); 

// 	 // 编译字符串对象为脚本对象
// 	 Handle<Script> script = Script::Compile(source); 

// 	 // 执行脚本，获取结果
// 	 Handle <Value> result = script->Run(); 

// 	 // 释放上下文资源
// 	 context.Dispose(); 

// 	 // 转换结果为字符串
// 	 String::AsciiValue ascii(result); 

// 	 printf("%s\n", *ascii); 

// 	 return 0; 
//  }

#include <v8.h>
#include <libplatform/libplatform.h>

int main(int argc, char* argv[]) {
    // Initialize V8.
    v8::V8::InitializeICUDefaultLocation(argv[0]);
    v8::V8::InitializeExternalStartupData(argv[0]);
    std::unique_ptr<v8::Platform> platform = v8::platform::NewDefaultPlatform();
    v8::V8::InitializePlatform(platform.get());
    v8::V8::Initialize();

    // Create a new Isolate and make it the current one.
    v8::Isolate::CreateParams create_params;
    create_params.array_buffer_allocator =
        v8::ArrayBuffer::Allocator::NewDefaultAllocator();
    v8::Isolate* isolate = v8::Isolate::New(create_params);
    {
        v8::Isolate::Scope isolate_scope(isolate);

        // Create a stack-allocated handle scope.
        v8::HandleScope handle_scope(isolate);

        // Create a new context.
        v8::Local<v8::Context> context = v8::Context::New(isolate);

        // Enter the context for compiling and running the hello world script.
        v8::Context::Scope context_scope(context);

        // Now you can use the context for executing JS code.
        // For example, you can create a string and compile it.
        v8::Local<v8::String> source =
            v8::String::NewFromUtf8Literal(isolate, "'Hello' + ', World!'");
        v8::Local<v8::Script> script = v8::Script::Compile(context, source).ToLocalChecked();

        // Run the script to get the result.
        v8::Local<v8::Value> result = script->Run(context).ToLocalChecked();

        // Convert the result to an UTF8 string and print it.
        v8::String::Utf8Value utf8(isolate, result);
        printf("%s\n", *utf8);
    }

    // Dispose the isolate and tear down V8.
    isolate->Dispose();
    v8::V8::Dispose();
    // v8::V8::ShutdownPlatform();
    delete create_params.array_buffer_allocator;

    return 0;
}