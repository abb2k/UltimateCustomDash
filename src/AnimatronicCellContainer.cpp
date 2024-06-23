
#include <AnimatronicCellContainer.h>
#include<iostream>    
#include<array>

#include <discriptionBox.h>
#include "customNightLayer.h"

using namespace std;
AnimatronicCellContainer* AnimatronicCellContainer::create(std::vector<AnimatronicCell*> animatronicCells, int CellArrayLength, int cellsPerRow, int endOfRowLength) {
    auto ret = new AnimatronicCellContainer();
    if (ret && ret->init(animatronicCells, CellArrayLength, cellsPerRow,endOfRowLength)) {
        ret->autorelease();
    } else {
        delete ret;
        ret = nullptr;
    }
    return ret;
}

bool AnimatronicCellContainer::init(std::vector<AnimatronicCell*> animatronicCells, int CellArrayLength, int cellsPerRow, int endOfRowLength){

    int currentRowCount = 0;
    int downAmount = 0;

    int lastInRowNum = cellsPerRow - endOfRowLength;

    for (int i = 0; i < CellArrayLength; i++){

        if (currentRowCount == cellsPerRow){
            currentRowCount = 0;
            downAmount++;
        }
        if (animatronicCells[i] != nullptr){

            float x = (40 * currentRowCount);
            float y = (-52 * downAmount);

            animatronicCells[i]->setPosition({x, y});
//            animatronicCells[i]->setZOrder(CellArrayLength - i);
            animatronicCells[i]->parent = this;

            if (currentRowCount >= lastInRowNum){
                animatronicCells[i]->lastInRow = true;
            }

            this->addChild(animatronicCells[i]);

            //+40 for left

            //-52 for down
        }
        currentRowCount++;
    }

    lengthofThings = CellArrayLength;

    std::string debugString = std::to_string(0);
    debugText = CCTextFieldTTF::create(debugString.c_str(), "chatFont.fnt", 4);
    debugText->setVisible(false);
    debugText->setPosition({416,0});

    this->addChild(debugText);

    scheduleUpdate();

    return true;
}

bool flashUp;
int FlashTime = 1;

void AnimatronicCellContainer::update(float delta){
        if (OpacityFlash >= 255){
            flashUp = false;
        }
        if (OpacityFlash <= 210){
            flashUp = true;
        }

        if (!flashUp){
            OpacityFlash -= FlashTime;
        }
        if (flashUp) {
            OpacityFlash +=  FlashTime;
        }

    int currentSet = 0;

    int overallToSend = 0;

    for (int i = 0; i < (int)this->getChildren()->count(); i++)
    {
        if (i != 0){
            if ((AnimatronicCell*)this->getChildren()->objectAtIndex(i) != nullptr){
                AnimatronicCell* thisone = (AnimatronicCell*)this->getChildren()->objectAtIndex(i);

                overallToSend += thisone->AILevel * 10;
            
                currentSet++;
            }
        }
    }
    
    customNightLayer* customNightMainlayer = (customNightLayer*)dad;

    customNightMainlayer->_MenuSideBar->OverallPoints = overallToSend;
}

void AnimatronicCellContainer::AddAll(int num){
    int currentSet = 0;
    for (int i = 0; i < (int)this->getChildren()->count(); i++)
    {
        if (i != 0){
            if ((AnimatronicCell*)this->getChildren()->objectAtIndex(i) != nullptr){
                AnimatronicCell* thisone = (AnimatronicCell*)this->getChildren()->objectAtIndex(i);

                thisone->AILevel += num;

                if(thisone->AILevel > 20){
                    thisone->AILevel = 20;
                }

                //(AnimatronicCell*)this->getChildren()->objectAtIndex(i)-> = thisone;
            
                currentSet++;
            }
        }
    }
}

void AnimatronicCellContainer::SetAll(int num){
    int currentSet = 0;
    for (int i = 0; i < (int)this->getChildren()->count(); i++)
    {
        if (i != 0){
            if ((AnimatronicCell*)this->getChildren()->objectAtIndex(i) != nullptr){
                AnimatronicCell* thisone = (AnimatronicCell*)this->getChildren()->objectAtIndex(i);
                if (num >= 0){
                    thisone->AILevel = num;
                }
                else {
                    thisone->AILevel = rand() % 21;
                }

                //this->getChildren()->index = thisone;
            
                currentSet++;
            }
        }
    }
}

void AnimatronicCellContainer::SetSpecific(std::string Name, int AILevel){
    int currentSet = 0;
    for (int i = 0; i < (int)this->getChildren()->count(); i++)
    {
        if (i != 0){
            if ((AnimatronicCell*)this->getChildren()->objectAtIndex(i) != nullptr){
                AnimatronicCell* thisone = (AnimatronicCell*)this->getChildren()->objectAtIndex(i);

                if (thisone->Name == Name){
                    thisone->AILevel = AILevel;
                    break;
                }
                currentSet++;
            }
        }
    }
}