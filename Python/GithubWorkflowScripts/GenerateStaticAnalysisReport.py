import os

current_directory = os.getcwd()
print("Current Directory:", current_directory)
aprg_directory = os.path.abspath(os.path.join(current_directory, "../.."))
