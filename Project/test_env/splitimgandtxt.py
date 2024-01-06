import os
import shutil
ORI_DIR="/home/quang/Desktop/SLP/IR_9class_merge_raw/train"
TAR_DIR="/home/quang/Desktop/SLP/final"
TXT_DIR=f"{TAR_DIR}/txt_data"
IMG_DIR=""f"{TAR_DIR}/img_data"


def mkdir(path):
    if not os.path.exists(path):
        os.mkdir(path)
        print("folder '{}' created ".format(path))
    else:
        print("folder {} already exists".format(path))

mkdir(TXT_DIR)
mkdir(IMG_DIR)
for folder in os.listdir(ORI_DIR):
    folder_name = folder.split(".")[0]
    mkdir(f"{TXT_DIR}/{folder_name}")
    mkdir(f"{IMG_DIR}/{folder_name}")
    print(folder_name)
    for file in os.listdir(os.path.join(ORI_DIR, folder)):
        if file.endswith(".txt"):
            shutil.copy(os.path.join(ORI_DIR, folder, file), f"{TXT_DIR}/{folder_name}/{file}")
        elif file.endswith('.jpg') or file.endswith('.png') or file.endswith('.jpeg'):
            shutil.copy(os.path.join(ORI_DIR, folder, file), f"{IMG_DIR}/{folder_name}/{file}")
        else:
            print("file {} is not txt or images".format(file))