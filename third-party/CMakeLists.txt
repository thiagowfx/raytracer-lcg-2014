execute_process(
  COMMAND qmake
  WORKING_DIRECTORY "${PCS_DETECTION_DIR}/"
)

execute_process(
  COMMAND make
  WORKING_DIRECTORY "${PCS_DETECTION_DIR}/"
)
