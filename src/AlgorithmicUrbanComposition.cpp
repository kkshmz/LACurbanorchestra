//
//  AlgorithmicUrbanComposition.cpp
//  LACAlgorithmicUrbanComposition
//
//  Created by Ryo Yumoto on 2019/03/21.
//

#include "AlgorithmicUrbanComposition.hpp"

using namespace AlgorithmicUrbanComposition;

void LACJsonData::load(const string& file_path){
    bool parsing_successful = load_data.open(file_path);
    if ( parsing_successful ) { cout << "------ load done -----" << "\n" ;}
    else{ cout << "can't load json" << "\n"; return;}
    
    splitFrame();
    splitCategories();
    createOscBuffer();
    
}


void LACJsonData::splitFrame(){
    for(auto i = 0; i < load_data.size(); ++i ){
        auto&& image_id = load_data[i]["image_id"].asString();
//        image_id.erase(0,4).erase(image_id.end()-4); // erase ".bmp"
        for(auto j = 0; j < image_id.size(); ++j){
            // ex) "000000572" to 572
            if (image_id[j] != '0'){
                frame_data[ofToInt(image_id)].push_back(load_data[i]);
                break;
            }
        }
    }

    cout << frame_data[572][0] << endl;
}

void LACJsonData::splitCategories(){
    
    for(auto frame_num = 0; frame_num < frame_data.size(); ++frame_num){
        for(auto i = 0; i < frame_data[frame_num].size(); ++i){
            string catid = frame_data[frame_num][i]["category"].asString();
            string clid  = frame_data[frame_num][i]["class_id"].asString();
            BlockData tmp { catid, clid };
            block_data_per_frame[frame_num].push_back(tmp);
        }
    }
    
}


void LACJsonData::createOscBuffer(){
    for(auto frame_num = 0; frame_num < block_data_per_frame.size(); ++frame_num){
        OscBuffer buffer {};
        
        for(auto i = 0; i < block_data_per_frame[frame_num].size(); ++i){
            if ( block_data_per_frame[frame_num][i].category == "1a"){
                buffer.object_num_per_category[0]++;
                buffer.object_num_per_class_id[0][block_data_per_frame[frame_num][i].class_id]++;
            }
            if ( block_data_per_frame[frame_num][i].category == "1b"){
                buffer.object_num_per_category[1]++;
                buffer.object_num_per_class_id[1][block_data_per_frame[frame_num][i].class_id]++;
            }
            
            if ( block_data_per_frame[frame_num][i].category == "2a"){
                buffer.object_num_per_category[2]++;
                buffer.object_num_per_class_id[2][block_data_per_frame[frame_num][i].class_id]++;
            }
            if ( block_data_per_frame[frame_num][i].category == "2b"){
                buffer.object_num_per_category[3]++;
                buffer.object_num_per_class_id[3][block_data_per_frame[frame_num][i].class_id]++;
            }
            
            if ( block_data_per_frame[frame_num][i].category == "3a"){
                buffer.object_num_per_category[4]++;
                buffer.object_num_per_class_id[4][block_data_per_frame[frame_num][i].class_id]++;
            }
            if ( block_data_per_frame[frame_num][i].category == "3b"){
                buffer.object_num_per_category[5]++;
                buffer.object_num_per_class_id[5][block_data_per_frame[frame_num][i].class_id]++;
            }
            
            if ( block_data_per_frame[frame_num][i].category == "4a"){
                buffer.object_num_per_category[6]++;
                buffer.object_num_per_class_id[6][block_data_per_frame[frame_num][i].class_id]++;
            }
            if ( block_data_per_frame[frame_num][i].category == "4b"){
                buffer.object_num_per_category[7]++;
                buffer.object_num_per_class_id[7][block_data_per_frame[frame_num][i].class_id]++;
            }
        }
        osc_buffers[frame_num] = buffer;
        
    }
  //  cout << osc_buffers[572].object_num_per_category[0] << endl;
   // cout << osc_buffers[572].object_num_per_class_id[0]["person"]<< endl;
    //inside object_nuM_per_category is 1a, 1b, 2a, 2b, 3a, 3b, 4a, 4b
}



void LACJsonData::sendOscMessage(int frame_num){
    
   // ofLog() << "Hello";
    ofxOscMessage m{};
    m.setAddress("/object_num");
    for(auto i = 0; i < osc_buffers[frame_num].object_num_per_category.size(); ++i){
        m.addIntArg(osc_buffers[frame_num].object_num_per_category[i]);
    }
    sender.sendMessage(m);
    
    for(auto i = 0; i < osc_buffers[frame_num].object_num_per_class_id.size(); ++i){
        ofxOscMessage m2{};
        // 0 > 1a
        // 1 > 1b
        // 2 > 2a
        // 3 > 2b
        // 4 > 3a
        // 5 > 3b
        // 6 > 4a
        // 7 > 4b
        for(auto&& m : osc_buffers[frame_num].object_num_per_class_id[i]){
            //i chooses which area
            //m.first class_id
            //m.second number
            cout << i << m.first << m.second << endl;
            // 0 > 1a
            if (i == 0) { ofxPublishOsc(HOST, 4001, "/"+ m.first, m.second); };
            // 1 > 1b
            if (i == 1) { ofxPublishOsc(HOST, 4002, "/"+ m.first, m.second); };
            // 2 > 2a
            if (i == 2) { ofxPublishOsc(HOST, 4003, "/"+ m.first, m.second); };
            // 3 > 2b
            if (i == 3) { ofxPublishOsc(HOST, 4004, "/"+ m.first, m.second); };
            // 4 > 3a
            if (i == 4) { ofxPublishOsc(HOST, 4005, "/"+ m.first, m.second); };
            // 5 > 3b
            if (i == 5) { ofxPublishOsc(HOST, 4006, "/"+ m.first, m.second); };
            // 6 > 4a
            if (i == 6) { ofxPublishOsc(HOST, 4007, "/"+ m.first, m.second); };
            // 7 > 4b
            if (i == 7) { ofxPublishOsc(HOST, 4008, "/"+ m.first, m.second); };
        }
    }
    
    
}

void LACJsonData::sendFrameNum(int _framenum){
    
    ofxPublishOsc(HOST,8888, "/movie_maxframe",_framenum);
}



