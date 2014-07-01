add_custom_target(doc
  /usr/bin/emacs "${CMAKE_CURRENT_SOURCE_DIR}/doc.org" --batch -f org-export-as-html --kill
  COMMAND /usr/bin/doxygen "${CMAKE_SOURCE_DIR}/lib/Doxyfile"
  COMMENT "Generate documentation"
  )
