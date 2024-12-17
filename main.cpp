 #include "../v8/include/v8.h"

 using namespace v8; 

 int main(int argc, char *argv[]) { 
	 // 创建一个句柄作用域 ( 在栈上 ) 
	 HandleScope handle_scope; 

	 // 创建一个新的上下文对象
	 Persistent<Context> context = Context::New(); 

	 // 进入上一步创建的上下文，用于编译执行 helloworld 
	 Context::Scope context_scope(context); 

	 // 创建一个字符串对象，值为'Hello, Wrold!', 字符串对象被 JS 引擎
	 // 求值后，结果为'Hello, World!'
	 Handle<String> source = String::New("'Hello' + ', World!'"); 

	 // 编译字符串对象为脚本对象
	 Handle<Script> script = Script::Compile(source); 

	 // 执行脚本，获取结果
	 Handle <Value> result = script->Run(); 

	 // 释放上下文资源
	 context.Dispose(); 

	 // 转换结果为字符串
	 String::AsciiValue ascii(result); 

	 printf("%s\n", *ascii); 

	 return 0; 
 }