set generateSDL 0
set generateDump 0
set generateAccess 1
set LICENSE demo.auth.codegenix

set ED_GENERATE_ED_CONST 0
set ED_GENERATE_EXPORT_CALL 0
set ED_01EXT_MULTI_OPTIONAL 1

# Generate everything as C++ files
set ED_C_EXT ".cpp"

set ED_C_ENCO_DECL ", TUserInterface& userInterface"
set ED_C_ENCO_CALL ", userInterface"
set ED_C_DECO_DECL $ED_C_ENCO_DECL 
set ED_C_DECO_CALL $ED_C_ENCO_CALL
set ED_DYNAMIC_DEFAULT 1