import os
import glob


# os.system("make build")
# print("Building finished")

os.chdir("./")
for f in glob.glob("*.diff"):
    if  os.stat(f).st_size == 0:
        print(f,"SUSSE")
    else:
        print(f,"Failed")