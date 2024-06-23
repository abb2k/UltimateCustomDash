#pragma once
#include <include.h>
#include "AnimatronicCell.h"
#include "animatronic.h"

class CNGameLayer : public cocos2d::CCLayer {
protected:
    virtual bool init(std::vector<animatronic*> animatronics, int office, bool frigidA, bool coinsA, bool batteryA, bool DDRepelA);
    virtual void keyBackClicked();
    virtual void update(float delta);

    virtual bool ccTouchBegan(CCTouch* touch, CCEvent* e);

    virtual void ccTouchEnded(CCTouch* touch, CCEvent* e);

    virtual void ccTouchCancelled(CCTouch* touch, CCEvent* e);

    virtual void ccTouchMoved(CCTouch* touch, CCEvent* e);

    virtual void onEnterTransitionDidFinish();

    virtual void keyDown(enumKeyCodes);
    virtual void keyUp(enumKeyCodes);

    bool buttonHoverLock = false;

    void OutsideOfAll(float);
    void AllCamsUpda(float);
    void deathscreenUpdate(float);
    void inJumpUpdate(float);
    void NightCompleteUpdate(float);

    void OnNightStart();
    bool nightStartedLock = false;

    void OnPowerDown();
    bool powerDownLock = false;

    void onCamsOpened();
public:
    static CNGameLayer* create(std::vector<animatronic*> animatronics, int office, bool frigidA, bool coinsA, bool batteryA, bool DDRepelA);
    void EnterLayer(std::vector<animatronic*> animatronics, int office, bool frigidA, bool coinsA, bool batteryA, bool DDRepelA);

    //management
    CCNode* MainCont;

    AudioSource* bgMusic;
    AudioSource* Ambiance;

    bool lookingTowardsRight;

    std::vector<animatronic*> animatronicsSave;

    int roundPointsWorth = 0;
    
    bool NIGHTSTARTED = false;
    CCSprite* BlackScreen;
    float blackScreenFade = 255;

    bool clicking = false;

    bool oneTimeClick = false;

    float camMovementSpeed = 0;

    CCNode* World;
    CCNode* Canvas;

    CCLabelTTF* debugText;

    CCSprite* CreateAnimatedSprite(float speed, int amoutOfFrames, std::string frames[]);

    void PlayAnimationOnSprite(CCSprite* sprite, float speed, int amoutOfFrames, std::string frames[]);
    CCRepeat* CreateAnimAction(float speed, int amoutOfFrames, std::string frames[], int repeats = 1);
    void PlayAnimationOnSpriteWithCallBack(CCSprite* sprite, float speed, int amoutOfFrames, std::string frames[], SEL_CallFunc callback);

    bool getHover(CCNode*);
    bool getHoveronPoint(CCNode*, CCPoint pointInWorldSpace);
    bool getHoverOnOther(CCNode*, CCNode* otherNode);
    bool getHoverSprite(CCSprite*, CCRenderTexture* renderTexture);
    bool getTouchOnSprite(CCSprite*, CCRenderTexture* renderTexture);
    bool getTouchOn(CCNode*);
    bool getTouchOn(CCNode*, CCTouch*);
    bool getTouchOnDouble(CCNode*);
    bool getHoldOn(CCNode*);

    GLubyte* getSpritePixelFromMouse(CCSprite*, CCRenderTexture* renderTexture);

    float randomFloat(int a, int b);
    int randomInt(int a, int b);
    float randomFloat();

    const char * const BoolToString(bool b);

    //office
    bool fanOn = true;
    bool doorLeftClosed = false;
    bool doorRightClosed = false;
    bool doorUpClosed = false;
    bool doorBottomRightClosed = false;

    CCSprite* office;
    CCSprite* officePowerDown;

    CCSprite* desk;
    CCNode* freedyNoseHitbox;
    CCSprite* CandyCoddet;
    float candyCoddetPulseTimer = 100;
    AudioSource* fanSound;

    //movement
    CCNode* MoveDetecSlowRight;
    CCNode* MoveDetecFastRight;
    CCNode* MoveDetecSlowLeft;
    CCNode* MoveDetecFastLeft;

    //flashlight
    CCSprite* Flashlight;
    bool FlashlightOn;
    bool canUseFlashlight = true;

    //night time
    CCLabelBMFont* nightTimer;
    float NightTime = 0;
    int NightMinutes = 0;
    float NightTimeOverall;

    CCLabelTTF* amTextDy;
    CCLabelBMFont* precentTextDy;

    //escape
    float escapeTimer = 0.5f;
    bool escaping = false;
    bool escaped;

    //office (again)
    CCSprite* doorLeft;
    CCSprite* doorUp;
    CCSprite* doorRight;
    CCSprite* doorBottomRight;

    //UI
    CCSprite* usageS1;
    CCSprite* usageS2;
    CCSprite* usageS3;
    CCSprite* usageS4;
    CCSprite* usageS5Red;
    CCSprite* usageS6Red;

    CCSprite* noiseS1;
    CCSprite* noiseS2;
    CCSprite* noiseS3Red;
    CCSprite* noiseS4Red;
    CCSprite* noiseS5Red;
    CCSprite* noiseS6Red;

    CCSprite* deathcoinSoff;
    CCSprite* deathcoinSon;

    int RedBarOpacity = 255;
    float RedBarFlashTimer = 0.1f;

    int noiseAmount = 0;
    int usageAmount = 0;

    //power
    float Power = 100;

    //visual
    float officeFlickerTimer = 0.5f;

    //UI
    float tempreture = 60;
    int heatMultiplier = 0;
    int CoolMultiplier = 0;
    CCLabelBMFont* tempretureText;
    CCLabelTTF* littlDotThing;
    CCNode* tempretureContainer;

    int fazCoins = 0;
    CCLabelBMFont* fazCoinsText;

    //floor sign
    CCSprite* floorSignLeft;
    CCSprite* floorSignRight;
    float doubleClickTimer = 0;
    bool floorSignOnLeft = true;

    //effects
    CCSprite* effectBlackscreen;
    float effectBlackscreenOpacity = 0;

    bool playBlackFlashes;
    float FlashRate;
    float flashForTime = 0;

    CCSprite* SpacialBlackscreen;
    float SpacialBlackscreenOpacity = 0;

    //mask
    CCSprite* MaskButton;
    CCSprite* Mask;
    bool InMask = false;
    CCNode* MaskButtonDetection;

    //CAMS
    bool camsDisabled;
    CCSprite* CamsButton;
    CCSprite* Cams;
    bool InCams = false;
    bool LookingAtCams;
    CCNode* CamsButtonDetection;
    CCSprite* CamStatic;
    float CamStaticOpacity = 255;
    CCNode* cameraView;
    CCNode* Cam01;
    CCNode* Cam02;
    CCNode* Cam03;
    CCNode* Cam04;
    CCNode* Cam05;
    CCNode* Cam06;
    CCNode* Cam07;
    CCSprite* Cam08S;
    CCSprite* deathCoinBuyButtton;
    bool baughtDeathCoin = false;
    bool confirmLookingAtCams = false;
    CCNode* Cam08;
    enum Cameras { Camera01, Camera02, Camera03, Camera04, Camera05, Camera06, Camera07, Camera08};
    Cameras currentCamSelected = Cameras::Camera01;
    void SwitchCamera(Cameras camera);
    float movementPauseTimer = 0;
    bool moveToRight = false;
    CCNode* cameraUI;
    CCNode* cameraOverallUI;
    CCNode* ventUI;
    CCNode* ductUI;
    CCSprite* Cam01ButtonOn;
    CCSprite* Cam01ButtonOff;
    CCSprite* Cam01ButtonText;
    CCSprite* Cam02ButtonOn;
    CCSprite* Cam02ButtonOff;
    CCSprite* Cam02ButtonText;
    CCSprite* Cam03ButtonOn;
    CCSprite* Cam03ButtonOff;
    CCSprite* Cam03ButtonText;
    CCSprite* Cam04ButtonOn;
    CCSprite* Cam04ButtonOff;
    CCSprite* Cam04ButtonText;
    CCSprite* Cam05ButtonOn;
    CCSprite* Cam05ButtonOff;
    CCSprite* Cam05ButtonText;
    CCSprite* Cam06ButtonOn;
    CCSprite* Cam06ButtonOff;
    CCSprite* Cam06ButtonText;
    CCSprite* Cam07ButtonOn;
    CCSprite* Cam07ButtonOff;
    CCSprite* Cam07ButtonText;
    CCSprite* Cam08ButtonOn;
    CCSprite* Cam08ButtonOff;
    CCSprite* Cam08ButtonText;
    CCNode* Cam01ButtonCont;
    CCNode* Cam02ButtonCont;
    CCNode* Cam03ButtonCont;
    CCNode* Cam04ButtonCont;
    CCNode* Cam05ButtonCont;
    CCNode* Cam06ButtonCont;
    CCNode* Cam07ButtonCont;
    CCNode* Cam08ButtonCont;
    bool inCamSys = true;
    bool inVentSys = false;
    bool inDuctSys = false;
    CCSprite* camSystem;
    CCSprite* ductSystem;
    CCSprite* ventSystem;
    CCSprite* systemButtonsBG;
    AudioSource* camsOpenSound;
    AudioSource* camsCloseSound;

    CCSprite* Cam05S;

    CCSprite* closeCurtainsB;

    CCNode* CamViewStatic;

    //VentSYS
    CCSprite* ventSnareEmptyRight;
    CCSprite* ventSnareEmptyLeft;
    CCSprite* ventSnareEmptyTop;
    CCSprite* ventSnareSelectedRight;
    CCSprite* ventSnareSelectedLeft;
    CCSprite* ventSnareSelectedTop;
    enum ventSnareLocation { right, up, left, None};
    ventSnareLocation snareLocation = ventSnareLocation::None;

    typedef struct ventPosition {
        float progressAmount = 0;
        enum ventsides {left, up, right};
        ventsides ventSide = ventsides::left;
    } ventPosition;

    ventPosition resetVentPos();

    CCPoint getVentPointFromPosition(ventPosition position);

    bool isTouchingVentSnare(ventPosition position);

    bool hasReachedEndOfVent(ventPosition position);

    //DuctSYS
    CCSprite* openDuctArrow;
    CCSprite* ClosedDuctX;
    CCSprite* OpenDuctLeftB;
    CCSprite* OpenDuctRightB;
    bool RightDuctOpen = false;

    CCNode* topleftContactPoint1;
    CCNode* topleftContactPoint2;

    CCNode* toprightContactPoint1;
    CCNode* toprightContactPoint2;

    CCNode* toplineContactPoint1;
    CCNode* toplineContactPoint2;
    CCNode* toplineContactPoint3;
    CCNode* toplineContactPoint4;
    CCNode* toplineContactPoint5;
    CCNode* toplineContactPoint6;
    CCNode* toplineContactPoint7;

    CCNode* topRightTurn;
    CCNode* topLeftTurn;

    CCNode* rightLineContactPoint1;
    CCNode* rightLineContactPoint2;
    CCNode* rightLineContactPoint3;
    CCNode* rightLineContactPoint4;

    CCNode* bottomRightTurn;

    CCNode* middleLineContactPoint1;
    CCNode* middleLineContactPoint2;
    CCNode* middleLineContactPoint3;
    CCNode* middleLineContactPoint4;
    CCNode* middleLineContactPoint5;
    CCNode* middleLineContactPoint6;
    CCNode* middleLineTurn;

    CCNode* middleLineUpContactPoint1;
    CCNode* middleLineUpContactPoint2;

    CCNode* rightMiddleTurn;

    CCNode* leftLineContactPoint1;
    CCNode* leftLineContactPoint2;
    CCNode* leftLineContactPoint3;
    CCNode* leftLineContactPoint4;

    CCNode* bottomLeftTurn;

    CCNode* leftMiddleTurn;

    CCNode* bottomRightLineContactPoint1;

    CCNode* bottomLeftLineContactPoint1;

    CCNode* bottomLeftToEndTurn;

    CCNode* bottomRightToEndTurn;

    CCNode* RightEndContactPoint;

    CCNode* LeftEndContactPoint;

    CCSprite* audioLore;

    enum ductLocations { 
        entrenceRight1,
        entrenceRight2,
        entrenceLeft1,
        entrenceLeft2,
        topLine1,
        topLine2,
        topLine3,
        topLine4,
        topLine5,
        topLine6,
        topLine7,
        topRightTurn_,
        topLeftTurn_,
        rightLine1,
        rightLine2,
        rightLine3,
        rightLine4,
        bottomRightTurn_,
        rightMiddleTurn_,
        middleLine1,
        middleLine2,
        middleLine3,
        middleLine4,
        middleLine5,
        middleLine6,
        middleLineTurn_,
        leftMiddleTurn_,
        middleLineUp1,
        middleLineUp2,
        leftLine1,
        leftLine2,
        leftLine3,
        leftLine4,
        bottomLeftTurn_,
        bottomRightLine1,
        bottomLeftLine1,
        bottomLeftToEndTurn_,
        bottomRightToEndTurn_,
        RightEnd,
        LeftEnd,
    };

    ductLocations audioLoreLocation;

    CCPoint getLocationFromDuctPos(ductLocations position);

    ductLocations moveDuctPos (ductLocations position);

    bool isOnClosedDuct(ductLocations position);

    bool hasReachedEndofDucts(ductLocations position);

    ductLocations resetDuctPosition();

    bool isInAudioLure(ductLocations position);

    //fazzxoin Randomazation
    typedef struct camFazCoins{
        CCSprite* sprite;
        Cameras inCamera;
    } camFazCoins;

    std::vector<camFazCoins*> CamCoins;
    int camCoinAmount;

    //special modes
    enum SpacialMode { PowerGenerator, SilentVentelation, Heater, PowerAC, GMB, Off};
    SpacialMode currSpacialMode = SpacialMode::Off;
    void setSpacialMode(SpacialMode mode);
    CCSprite* powerGenButton;
    CCSprite* silVentButton;
    CCSprite* heaterButton;
    CCSprite* powerACButton;
    CCSprite* GMBButton;
    CCSprite* spacialsOffButton;
    CCSprite* spacialUsed;

    //music box
    CCNode* musicBoxCont;
    CCSprite* windBoxOff;
    CCSprite* windBoxOn;
    CCSprite* boxWindBar;
    float boxChargeMinitimer = 0;

    //change music
    CCSprite* ChangeMusicButton;
    enum musics { music1, music2, music3, music4};
    musics currMusic = musics::music1;
    void changeMusic();
    CCSprite* AONLY;
    AudioSource* musicBoxAudio = nullptr;
    std::string currMusicString = "musicbox.mp3"_spr;

    //reset ventilation
    CCSprite* resetVentelation;
    CCSprite* resetVentelationActive;
    CCSprite* venWarnMask;
    CCSprite* venWarnCams;
    float vetelationTimer = 30;
    int vetolationMutliplier = 1;
    bool canResetVen = false;

    CCSprite* jumpEmpty;
    CCSprite* Jumpscare(CCRepeat* animation, std::string jumpSoundEffect, bool noneLethal, bool dontRemoveMask, bool dontRemoveCams, float scaling = 5,float jumpOpacity = 255, SEL_CallFunc callback = NULL, CCObject* CallbackTarget = nullptr, bool addToCanvas = true, bool disableShake = false);
    void jumpscareEnded();
    void jumpscareEndedNonLethal();
    float officeRotation = 0;
    bool rotGoUp = true;
    bool inJumpscare = false;
    bool DEATHSCREEN = false;
    float DeathDelay = 1;
    CCSprite* redScreen;
    CCSprite* redVignette;
    float redVOpactiy = 255;
    CCSprite* gameOverText;
    CCLabelBMFont* gameOverTimeText;
    std::vector<CCSprite*> jumpscares;
    AudioSource* jumpscaresound = nullptr;

    bool nightComplete = false;
    CCSprite* udidit;
    float udiditOpacity = 0;
    float delayForDrop = 1.25f;
    CCSprite* highScoreText;
    float highScoreFlashTimer = 0;
    CCLabelBMFont* highScoreTextDy;
    int scoreCounter = 0;
    float countTimer = 0.045f;
    CCSprite* greatJob;
    CCSprite* fantastic;
    CCSprite* amazing;
    CCSprite* stupendous;
    CCSprite* perfect;
    CCSprite* unbeatable;
    float fireworkBlastTimer = 0;
    AudioSource* completionMusic;

    //debugging
    bool clickingUpArrow;
    bool clickingDownArrow;
    bool clickingRightArrow;
    bool clickingLeftArrow;

    //other stuff
    void CharacterBlock();

    void FlashEffects(float time, SEL_CallFunc callbackWhenDone = NULL, CCObject* caller = NULL);
    void removeFromFlashEffects(float time);

    CCSprite* CreatePoof();
    std::vector<CCSprite*> poofs;
    void endedPoof();

    bool clickingC;

    bool blockDoorUsage;

    void PutDownCams();

    void disableFlashlight();

    bool enterClicked;

    void PreloadImages(std::vector<std::string> images);

    bool deathrotationsDisabled;

    bool fastVentelation;
};