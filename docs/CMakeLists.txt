execute_process(COMMAND /usr/bin/emacs "${CMAKE_CURRENT_SOURCE_DIR}/doc.org" --batch -f org-export-as-html --kill)
execute_process(COMMAND /usr/bin/doxygen "${CMAKE_SOURCE_DIR}/lib/Doxyfile")
