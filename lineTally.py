#quick script to find the number of lines of code in the src folder
import os
directory = os.getcwd() + "\\src"
total_lines = 0
for root, dirs, files in os.walk(directory):
	#ignore any of the code i didnt write, not trying to steal credit
	if "Platform" in root or "Utility" in root or "box2d" in root:
		continue
	for file in files:
		file_path = os.path.join(root,file)
		with open(file_path,'r', encoding = "utf-8", errors="ignore") as f:
			total_lines += len(f.readlines())
print("Directory contains",total_lines, "lines of code")