use ast::annotation::*;

#[derive(Debug)]
pub enum TypeQualifier
{
    Const
}

#[derive(Debug)]
pub enum DataType
{
    U8,
    I8,
    U16,
    I16,
    U32,
    I32,
    U64,
    I64,
    F32,
    F64,
    Char,
    WChar,
    Void,
    SizeT,
    Result,
    NamedType {name: String}
}

#[derive(Debug)]
pub struct ModifiedType
{
    pub qualifier: Option<TypeQualifier>,
    pub data_type: DataType,
    pub indirection_count: u32
}

#[derive(Debug)]
pub struct TypeDecl
{
    pub annotation: Option<Annotation>,
    pub data_type: ModifiedType
}
