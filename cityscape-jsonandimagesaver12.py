
# coding: utf-8

# In[1]:

import os
import sys
import random
import math
import numpy as np
import scipy.misc
import matplotlib
import matplotlib.pyplot as plt
import skimage
from skimage import io

import coco
import utils
import model as modellib
import visualize
import PIL

import json
import collections
import cv2

from PIL import Image

#%matplotlib inline 

# Root directory of the project
ROOT_DIR = os.getcwd()

# Directory to save logs and trained model
MODEL_DIR = os.path.join(ROOT_DIR, "logs")

# Path to trained weights file
# Download this file and place in the root of your 
# project (See README file for details)
COCO_MODEL_PATH = os.path.join(ROOT_DIR, "mask_rcnn_coco.h5")

# Directory of images to run detection on
IMAGE_DIR = "/home/kkshmz-rzm/bltb3-2/shibuya-4k/C0012"


# In[2]:

class InferenceConfig(coco.CocoConfig):
    # Set batch size to 1 since we'll be running inference on
    # one image at a time. Batch size = GPU_COUNT * IMAGES_PER_GPU
    GPU_COUNT = 1
    IMAGES_PER_GPU = 1

config = InferenceConfig()
# config.print()


# In[3]:

# Create model object in inference mode.
model = modellib.MaskRCNN(mode="inference", model_dir=MODEL_DIR, config=config)

# Load weights trained on MS-COCO
model.load_weights(COCO_MODEL_PATH, by_name=True)


# In[4]:

# COCO Class names
# Index of the class in the list is its ID. For example, to get ID of
# the teddy bear class, use: class_names.index('teddy bear')
class_names = ['BG', 'person', 'bicycle', 'car', 'motorcycle', 'airplane',
               'bus', 'train', 'truck', 'boat', 'traffic_light',
               'fire_hydrant', 'stop_sign', 'parking meter', 'bench', 'bird',
               'cat', 'dog', 'horse', 'sheep', 'cow', 'elephant', 'bear',
               'zebra', 'giraffe', 'backpack', 'umbrella', 'handbag', 'tie',
               'suitcase', 'frisbee', 'skis', 'snowboard', 'sports_ball',
               'kite', 'baseball_bat', 'baseball_glove', 'skateboard',
               'surfboard', 'tennis_racket', 'bottle', 'wine glass', 'cup',
               'fork', 'knife', 'spoon', 'bowl', 'banana', 'apple',
               'sandwich', 'orange', 'broccoli', 'carrot', 'hot_dog', 'pizza',
               'donut', 'cake', 'chair', 'couch', 'potted_plant', 'bed',
               'dining_table', 'toilet', 'tv', 'laptop', 'mouse', 'remote',
               'keyboard', 'cell_phone', 'microwave', 'oven', 'toaster',
               'sink', 'refrigerator', 'book', 'clock', 'vase', 'scissors',
               'teddy_bear', 'hair_drier', 'toothbrush']


# In[12]:


#sys.path.append(os.path.join(ROOT_DIR, "samples/coco/"))  # To find local version
#import coco

#get_ipython().magic('matplotlib inline')

# Directory to save logs and trained model
MODEL_DIR = os.path.join(ROOT_DIR, "logs")

# Local path to trained weights file
COCO_MODEL_PATH = os.path.join(ROOT_DIR, "mask_rcnn_coco.h5")
# Download COCO trained weights from Releases if needed
if not os.path.exists(COCO_MODEL_PATH):
    utils.download_trained_weights(COCO_MODEL_PATH)


# Directory of images to run detection on


SAVE_DIR = os.path.join(ROOT_DIR, "output/C0012/")
with open('C0012.json', 'a') as outfile:
    for f in sorted(os.listdir(IMAGE_DIR)):
        print (f)
        image = io.imread(os.path.join(IMAGE_DIR,f))
        img = cv2.imread(os.path.join(IMAGE_DIR,f))
        results = model.detect([image],verbose=0)
        r = results[0]
        imagename = os.path.join(SAVE_DIR+f)
        visualize.save_image(image, imagename,r['rois'], r['masks'], r['class_ids'], r['scores'],class_names)
        for i in range(len(r['scores'])):
            y2 = r['rois'][i][2]
            y1 = r['rois'][i][0]
            bboxwidth = y2-y1
            x2 = r['rois'][i][3]
            x1 = r['rois'][i][1]
            bboxheight = x2-x1
            bboxcenter = (bboxwidth/2)+(bboxheight/2)
            dimensions = img.shape
            height = img.shape[0]
            width = img.shape[1]
            objectData = {}
            objectData['image_id'] = f
            objectData['class_id'] = class_names[int(r['class_ids'][i])]
            objectData['confidence'] = float(r['scores'][i])
            objectData['x'] = ((int(x2)-int(x1))/2)+x1
            objectData['y'] = ((int(y1)-int(y2))/2)+y1
           
            #print(objectData)
            json.dump(objectData,outfile)
            outfile.write("\n")  
            
            # Add newline cause Py JSON does not
            
            
#             plt.savefig(os.path.join(SAVE_DIR, f),bbox_inches='tight', pad_inches=-0.5,orientation= 'landscape')
            #cv2.imwrite(os.path.join(SAVE_DIR, f), image)
#         print(r['scores'])
#         print(r['class_ids'])
#         objectData = {}
#         objectData['class_id'] = r['class_ids']
#         objectData['confidence'] = r['scores']
#         objectData['center'] = bboxcenter
#         print(objectData)
#         json.dump(objectData,outfile)
        


# In[ ]:



