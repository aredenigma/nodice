/*
 * Sifteo SDK Example.
 */

#include <sifteo.h>
#include <sifteo/video/color.h>
#include "assets.gen.h"
using namespace Sifteo;

Random gRandom;

static AssetSlot MainSlot = AssetSlot::allocate()
.bootstrap(wibb);

static Metadata M = Metadata()
    .title("Sensors SDK Example")
    .package("com.sifteo.sdk.sensors", "1.1")
    .icon(Icon)
    .cubeRange(0, CUBE_ALLOCATION);

static VideoBuffer vid[CUBE_ALLOCATION];
static TiltShakeRecognizer motion[CUBE_ALLOCATION];

static String<16> names[6];
static String<16> verbs[9];
static String<16> adjectives[9];
static String<16> nouns[12];
static String<16> prepositions[8];
static String<16> nouns2[12];
static String<16> modifiers[6];

class SensorListener {

public:
    struct Counter {
        unsigned touch;
        unsigned neighborAdd;
        unsigned neighborRemove;
    } counters[CUBE_ALLOCATION];
    
    unsigned myRandomWordId1;
    unsigned myRandomWordId2;
    unsigned myRandomWordId3;
    unsigned myRandomWordId4;
    unsigned myRandomWordId5;
    unsigned myRandomWordId6;

    void install()
    {
        Events::neighborAdd.set(&SensorListener::onNeighborAdd, this);
        Events::neighborRemove.set(&SensorListener::onNeighborRemove, this);
        Events::cubeAccelChange.set(&SensorListener::onAccelChange, this);
       // Events::cubeTouch.set(&SensorListener::onTouch, this);
       // Events::cubeBatteryLevelChange.set(&SensorListener::onBatteryChange, this);
        Events::cubeConnect.set(&SensorListener::onConnect, this);

        // Handle already-connected cubes
        for (CubeID cube : CubeSet::connected())
            onConnect(cube);
    }

private:
    
    void onConnect(unsigned id)
    {
        CubeID cube(id);
        myRandomWordId1 = 0;
        myRandomWordId2 = 0;
        myRandomWordId3 = 0;
        myRandomWordId4 = 0;
        myRandomWordId5 = 0;
        myRandomWordId6 = 0;
        
        String<64> str;
        
        bzero(counters[id]);
        
        vid[id].initMode(BG0_ROM);
        vid[id].attach(id);
        motion[id].attach(id);
        
        switch(id){
            default:
            case 0: 
                str <<  "Hi! I'm the \n" << names[0] << " cube.";
                //vid[id].attach(cube);
                //vid[id].bg0.image(vec(0,0), blue);
                break;
            case 1:
                str <<  "Oi! Here there \nbe " << names[1] << "S.";
                //vid[id].attach(cube);
                //vid[id].bg0.image(vec(0,0), yellow);
       
                break;
            case 2:
                str <<  "Yo! " << names[2] << " cube \nreporting \nfor duty.";
                //vid[id].attach(cube);
                //vid[id].bg0.image(vec(0,0), green);
   
                break;
            case 3:
                str <<  "Hiya! I have \n" << names[3] << "S.";
                //vid[id].attach(cube);
                //vid[id].bg0.image(vec(0,0), green);
                
                break;
            case 4:
                str <<  "Have another \n" << names[4] << ".";
                //vid[id].attach(cube);
                //vid[id].bg0.image(vec(0,0), green);
                
                break;
            case 5:
                str <<  "I'm here to \ngive you \n" << names[5] << ".";
                //vid[id].attach(cube);
                //vid[id].bg0.image(vec(0,0), green);
                
                break;
        }
       vid[cube].bg0rom.text(vec(1,3), str);
        
        // Draw initial state for all sensors
        onAccelChange(cube);
        //onBatteryChange(cube);
        //onTouch(cube);
        drawNeighbors(cube);
        

    }

    

   /* void onBatteryChange(unsigned id)
    {
        CubeID cube(id);
        String<32> str;
        str << "bat:   " << FixedFP(cube.batteryLevel(), 1, 3) << "\n";
        vid[cube].bg0rom.text(vec(1,13), str);
    }*/

   /* void onTouch(unsigned id)
    {
        CubeID cube(id);
        counters[id].touch++;
        LOG("Touch event on cube #%d, state=%d\n", id, cube.isTouching());

        String<32> str;
        str << "touch: " << cube.isTouching() <<
            " (" << counters[cube].touch << ")\n";
        vid[cube].bg0rom.text(vec(1,9), str);
    } */

    void onAccelChange(unsigned id)
    {
        CubeID cube(id);
        auto accel = cube.accel();

        String<64> str;
        /*
        str << "acc: "
            << Fixed(accel.x, 3)
            << Fixed(accel.y, 3)
            << Fixed(accel.z, 3) << "\n";
         */

        unsigned changeFlags = motion[id].update();
        if (changeFlags) {
            // Tilt/shake changed
            
            myRandomWordId1 = (int) gRandom.uniform(0, 8.999999);
            myRandomWordId2 = (int) gRandom.uniform(0, 8.999999);
            myRandomWordId3 = (int) gRandom.uniform(0, 11.999999);
            myRandomWordId4 = (int) gRandom.uniform(0, 7.999999);
            myRandomWordId5 = (int) gRandom.uniform(0, 11.999999);
            myRandomWordId6 = (int) gRandom.uniform(0, 5.999999);
            
            switch(id){
                default:
                case 0:
                    // so,ethjing;
                    str <<  "Please " << verbs[myRandomWordId1] << " \n";
                    break;
                case 1:
                    str <<  "the " << adjectives[myRandomWordId2] << " \n";
                    // what to do if id == 1
                    break;
                case 2:
                    str << "" << nouns[myRandomWordId3] << " \n";
                    // what to do if id == 1
                    break;
                case 3:
                    str << "" << prepositions[myRandomWordId4] << " \n";
                    // what to do if id == 1
                    break;
                case 4:
                    str << "" << nouns2[myRandomWordId5] << " \n";
                    // what to do if id == 1
                    break;
                case 5:
                    str << "" << modifiers[myRandomWordId6] << " \n";
                    // what to do if id == 1
                    break;
            }
            
            
            // LOG("Tilt/shake changed, flags=%08x\n", changeFlags);

            /*
            auto tilt = motion[id].tilt;
            str << "tilt:"
                << Fixed(tilt.x, 3)
                << Fixed(tilt.y, 3)
                << Fixed(tilt.z, 3) << "\n";

            str << "shake: " << motion[id].shake;
            */
        }

        vid[cube].bg0rom.text(vec(1,10), str);
    }

    void onNeighborRemove(unsigned firstID, unsigned firstSide, unsigned secondID, unsigned secondSide)
    {
        LOG("Neighbor Remove: %02x:%d - %02x:%d\n", firstID, firstSide, secondID, secondSide);

        if (firstID < arraysize(counters)) {
            counters[firstID].neighborRemove++;
            drawNeighbors(firstID);
        }
        if (secondID < arraysize(counters)) {
            counters[secondID].neighborRemove++;
            drawNeighbors(secondID);
        }
    }

    void onNeighborAdd(unsigned firstID, unsigned firstSide, unsigned secondID, unsigned secondSide)
    {
        LOG("Neighbor Add: %02x:%d - %02x:%d\n", firstID, firstSide, secondID, secondSide);

        if (firstID < arraysize(counters)) {
            counters[firstID].neighborAdd++;
            drawNeighbors(firstID);
        }
        if (secondID < arraysize(counters)) {
            counters[secondID].neighborAdd++;
            drawNeighbors(secondID);
        }
    }

    void drawNeighbors(CubeID cube)
    {
        Neighborhood nb(cube);

 /*       String<64> str;
        str << "nb "
            << Hex(nb.neighborAt(TOP), 2) << " "
            << Hex(nb.neighborAt(LEFT), 2) << " "
            << Hex(nb.neighborAt(BOTTOM), 2) << " "
            << Hex(nb.neighborAt(RIGHT), 2) << "\n";

        str << "   +" << counters[cube].neighborAdd
            << ", -" << counters[cube].neighborRemove
            << "\n\n"; 

        draw.text(vec(1,6), str); */
    
        BG0ROMDrawable &draw = vid[cube].bg0rom;
        drawSideIndicator(draw, nb, vec( 1,  0), vec(14,  1), TOP);
        drawSideIndicator(draw, nb, vec( 0,  1), vec( 1, 14), LEFT);
        drawSideIndicator(draw, nb, vec( 1, 15), vec(14,  1), BOTTOM);
        drawSideIndicator(draw, nb, vec(15,  1), vec( 1, 14), RIGHT);
    }

    static void drawSideIndicator(BG0ROMDrawable &draw, Neighborhood &nb,
        Int2 topLeft, Int2 size, Side s)
    {
        unsigned nbColor = draw.ORANGE;
        draw.fill(topLeft, size,
            nbColor | (nb.hasNeighborAt(s) ? draw.SOLID_FG : draw.SOLID_BG));
    }
};


void main()
{
    static SensorListener sensors;
    
    // V A N
    // 0 1 2

    names[0]      = "VERB";
    names[1]      = "ADJECTIVE";
    names[2]      = "NOUN";
    names[3]      = "PREPOSITION";
    names[4]      = "NOUN";
    names[5]      = "MODIFIERS";
    
    verbs[0]      = "pet    ";
    verbs[1]      = "kiss   ";
    verbs[2]      = "comb   ";
    verbs[3]      = "nuzzle ";
    verbs[4]      = "kiss   ";
    verbs[5]      = "punt   ";
    verbs[6]      = "release";
    verbs[7]      = "ignore ";
    verbs[8]      = "debug  ";
    
    adjectives[0] = "dead    ";
    adjectives[1] = "furry   ";
    adjectives[2] = "grumpy  ";
    adjectives[3] = "cute    ";
    adjectives[4] = "awkward ";
    adjectives[5] = "manic   ";
    adjectives[6] = "volatile";
    adjectives[7] = "shiny   ";
    adjectives[8] = "alarming";
    
    nouns[0]      = "cat      ";
    nouns[1]      = "pony     ";
    nouns[2]      = "turtle   ";
    nouns[3]      = "koala    ";
    nouns[4]      = "code     ";
    nouns[5]      = "cabbage  ";
    nouns[6]      = "hounds   ";
    nouns[7]      = "unicorn  ";
    nouns[8]      = "hermit   ";
    nouns[9]      = "seamonkey";
    nouns[10]      = "bonsai  ";
    nouns[11]      = "turkey  ";
    
    prepositions[0]      = "with       ";
    prepositions[1]      = "from       ";
    prepositions[2]      = "in         ";
    prepositions[3]      = "across from";
    prepositions[4]      = "on top of  ";
    prepositions[5]      = "for        ";
    prepositions[6]      = "to         ";
    prepositions[7]      = "by         ";
    
    nouns2[0]      = "gong        ";
    nouns2[1]      = "spatula     ";
    nouns2[2]      = "soccer cleat";
    nouns2[3]      = "sofa        ";
    nouns2[4]      = "custody     ";
    nouns2[5]      = "newspaper   ";
    nouns2[6]      = "toes        ";
    nouns2[7]      = "face        ";
    nouns2[8]      = "pickle      ";
    nouns2[9]      = "magic wand  ";
    nouns2[10]      = "kryptonite ";
    nouns2[11]      = "sombrero   ";
    
    modifiers[0]      = "a     ";
    modifiers[1]      = "the   ";
    modifiers[2]      = "some  ";
    modifiers[3]      = "my    ";
    modifiers[4]      = "your  ";
    modifiers[5]      = "their ";
    

    sensors.install();

    // We're entirely event-driven. Everything is
    // updated by SensorListener's event callbacks.
    while (1)
        System::paint();
}
