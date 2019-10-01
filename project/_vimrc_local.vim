" Project level configuration
" Required newest nvim-as-ide.
"let g:ale_c_gcc_exectuable = "avr-gcc"
let g:ale_cpp_gcc_exectuable = "avr-gcc"

"let g:ale_cpp_gcc_options = 
let g:ale_cpp_gcc_options = "-std=c++17" . system("./get_CPPFLAGS.sh")
