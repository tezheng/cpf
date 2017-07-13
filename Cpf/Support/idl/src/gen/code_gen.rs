use gen::*;
use ast::*;
use context::*;

pub enum ConstType
{
	U32
}

pub trait CodeGenerator
{
	fn log(&self, context: &Context);
	fn string_out(&mut self, s: &str) {}
	fn indent_out(&mut self, s: &str) {}
	fn indent(&mut self) {}
	fn unindent(&mut self) {}

	fn generate(&mut self, tree: ASTRef, output: &str);
	fn push_scope(&mut self, name: &str);
	fn pop_scope(&mut self);
	fn get_scope(&self) -> Scope {Scope::new("")}
	fn add_result(&mut self, name: &str, is_error: bool, subsys: &str, code: &str) -> bool {true}
	fn add_constant(&mut self, t: ConstType, name: &str, value: u32) -> bool {true}
}

pub fn get_generator(language: Language) -> Option<Box<CodeGenerator>>
{
	match language
	{
		Language::Rust => {Some(Box::new(rust::Generator::new()))},
		Language::Python3 => {Some(Box::new(python3::Generator {}))},
		Language::Cpp => {Some(Box::new(cpp::Generator {}))}
		_ => None
	}
}