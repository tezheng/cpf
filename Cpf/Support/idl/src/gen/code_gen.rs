use gen::*;
use ast::*;

pub enum Language
{
	Rust,
	Python3,
	Cpp
}

pub trait CodeGenerator
{
	fn generate(&self, tree: NodeRef<Data>, ooutput: &str);
}

pub fn get_generator(language: Language) -> Option<Box<CodeGenerator>>
{
	match language
	{
		Language::Rust => {Some(Box::new(rust::Generator {}))},
		Language::Python3 => {Some(Box::new(python3::Generator {}))},
		Language::Cpp => {Some(Box::new(cpp::Generator {}))}
	}
}
