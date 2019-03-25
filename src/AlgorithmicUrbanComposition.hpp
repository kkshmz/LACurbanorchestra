//
//  AlgorithmicUrbanComposition.hpp
//  LACAlgorithmicUrbanComposition
//
//  Created by Ryo Yumoto on 2019/03/21.
//

#ifndef AlgorithmicUrbanComposition_hpp
#define AlgorithmicUrbanComposition_hpp

#include "ofMain.h"
#include "ofxOsc.h"
#include "ofxPubSubOsc.h"
#include "ofxJSON.h"

namespace AlgorithmicUrbanComposition{
//constexpr auto HOST { "127.0.0.1"};
constexpr auto HOST {"192.168.10.10"};
constexpr auto PORT {4624};
static const vector<string> kJsonKeyName{
    "image_id", "class_id", "x", "y", "confidence", "category"
};
static const vector<string> kClassList {
     "person", "bicycle", "car", "motorcycle", "airplane",
    "bus", "train", "truck", "boat", "traffic_light",
    "fire_hydrant", "stop_sign", "bench", "bird",
    "cat", "dog", "horse",  "cow", "elephant", "bear",
    "zebra", "giraffe", "backpack", "umbrella", "handbag", "tie",
    "suitcase", "frisbee", "skis", "snowboard",
    "kite", "baseball_bat", "baseball_glove", "skateboard",
    "surfboard", "tennis_racket", "bottle", "cup",
    "fork", "knife", "spoon", "bowl", "banana", "apple",
     "chair", "couch", "potted_plant", "bed",
    "dining_table", "toilet", "tv", "laptop", "mouse", "remote",
     "cell_phone", "oven",
    "sink", "refrigerator", "book", "clock", "vase"
};

static const vector<string> kCategory{
    "1a","1b", "2a", "2b", "3a", "3b", "4a", "4b"
};

class LACJsonData {
public:
    LACJsonData(){ sender.setup(HOST, PORT);}
    ~LACJsonData(){}
    
    void load(const string& file_path);
    void sendOscMessage(int frame_num);
    void sendFrameNum( int _framenum);
    
    const char* getHost() noexcept { return HOST;}
    int getPort() noexcept { return PORT;}
    
    
private:
    struct BlockData{
        string category;
        string class_id;
    };
    
    struct OscBuffer {
        OscBuffer() {
            object_num_per_category.assign(8,0);
            object_num_per_class_id.resize(8);
        }
        vector<int> object_num_per_category;
        vector<map<string, int>> object_num_per_class_id; //person, how many
    };
    
    ofxJSONElement load_data;
    ofxOscSender sender;
    void splitFrame();
    void splitCategories();
    void createOscBuffer();
    unordered_map<int, vector<ofxJSONElement>> frame_data;
    unordered_map<int, vector<BlockData>> block_data_per_frame;
    unordered_map<int, std::map<string, int>> object_num_per_frame;
    unordered_map<int, OscBuffer> osc_buffers;
    
    
};
}











#endif /* AlgorithmicUrbanComposition_hpp */
