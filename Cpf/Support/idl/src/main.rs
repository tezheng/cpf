pub mod idl;
pub mod ast;

#[test]
fn test_idl()
{
	let result = idl::parse_Numeric("123");
	match *result.unwrap()
	{
		ast::Numeric::Signed(value) => {println!("Value: {}", value);},
		ast::Numeric::Unsigned(value) => {println!("Value: {}", value);},
		ast::Numeric::Float(value) => {println!("Value: {}", value);}
	}
	println!("--------------");
}

fn main()
{
	let test_string =
	"import something
	namespace test {}";

	println! ("------------------------------- Parsing IDL.");
	let result = idl::parse_IDL(test_string);
	println! ("Tree: {:?}", result);
	println! ("-------------------------------");
}