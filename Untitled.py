
# coding: utf-8

# In[ ]:


import os
import sys
import random
import math
import json
import codecs
import numpy

ROOT_DIR = os.getcwd()

with open('/Users/kkshmzmbp/11-projects/1903-urbanorchestra/99-finaldata/json/1080p-scaled/scaled-C0017.json') as f:
    data = json.load(f)
    # k = 8580
    unique_list = list()
    newlist = list()
    x = list(range(1,5460))
    z = 62866
    for i in range(len(list(data))):
        data[i]['image_id'] = data[i]['image_id'].lstrip('0')
        data[i]['image_id'] = os.path.splitext(data[i]['image_id'])[0]
       # print(data[i]['image_id'])
       # data[i]['image_id'] = 8580
        #print(type(data[i]['image_id'])) // this returns as str
        #print(data[i]['image_id'])
        
        # unique_list = list()
        for f in [int(data[i]['image_id'])]:
            newz  = z + f
            newlist.append(newz)
            if f not in unique_list:
                unique_list.append(f)
    #print(unique_list) 
    #appends all the values into a list
    #[1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13,] etc
    #print(newlist)





    for j in range(len(list(data))):
        data[j]['image_id'] = newlist[j]
    #     for k in [int(data[j]['image_id'])]:
    #         #print(k) prints the unqiue values of json 0 0 1 2 2 2 3 
    #         #print(unique_list[0]) new counter
    #         #print(j) regular counter 
    #         newz  = z + k
    #         newlist.append(newz)
    #          if k == unique_list[j]:
    #              k = x[j]
    
                #print(type(unique_list))
            # if f == unique_list[i]:
            #         f = x[i]
        # print(unique_list)
        # for j in [int(data[i]['image_id'])]:
        #     #  print(j)
        #         if j == unique_list[i]:
        #             j = x[i]
            
            #print(f)
       # print(data[i]['image_id'])
        # for f in (data[i]['image_id']):
        #     f = 8580
        #     f = f+1
        #     print (f)
        #  #   print(i)
       # if data[i]['image_id']
        # data[i]['image_id'] = k
        # k = k +1
        # for j in data[i]['image_id']:
        #         j = k
        #         k = k +1
        #         print (j)

            
#             print(value)

# for k in range(5460,7321):
#     with open('/Users/kkshmzmbp/11-projects/1903-urbanorchestra/99-finaldata/json/copy-C0012.json') as f:
#         data = json.load(f)
#         for j in range(len(list(data))):
#             data[j]['image_id'] = k
   
#                     print(k)
with open('/Users/kkshmzmbp/11-projects/1903-urbanorchestra/99-finaldata/json/scaled-finalized/9-C17.json', 'w') as outfile:
    #json.dumps(data,outfile)
     json.dump(data, outfile, indent=2, separators=(',', ': '), sort_keys=True)


# with open('/Users/kkshmzmbp/11-projects/1903-urbanorchestra/99-finaldata/json/copy-C0012.json') as f:
#     data = json.load(f)
#     for i in range(len(list(data))):
#         for value in data[i]['image_id']:
#             # temp = [value['image_id']]
#             print(value)

# with open('/Users/kkshmzmbp/11-projects/1903-urbanorchestra/99-finaldata/json/test-C0012.json', 'w') as outfile:
#     #json.dumps(data,outfile)
#     json.dump(data, outfile, indent=2, separators=(',', ': '), sort_keys=True)

# In[ ]:



