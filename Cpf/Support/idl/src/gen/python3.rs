use ast;
use gen::code_gen::CodeGenerator;

pub struct Generator
{

}

#[allow(unused_variables)]
impl CodeGenerator for Generator
{
	fn generate(&mut self, tree: ast::ASTRef, output: &str)
	{
		println!("Generating rust code to: {}", output);
	}
}
