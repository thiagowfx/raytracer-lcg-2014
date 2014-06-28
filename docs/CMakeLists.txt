execute_process(COMMAND /usr/bin/emacs "${CMAKE_CURRENT_SOURCE_DIR}/doc.org" --batch -f org-export-as-html --kill)
