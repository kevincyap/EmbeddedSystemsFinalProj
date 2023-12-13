

#include <Adafruit_CircuitPlayground.h>
#include <Adafruit_Circuit_Playground.h>

#define BUFF_LEN 20
#define LOG_LEN 20
//Options are GRAPH, STATE, and PREDICT
#define PREDICT

//If defined, will use the 10th neopixel to display the current state
#define DISPLAY_STATE

//Threshold for detecting movement
#define MOVEMENT_THRESHOLD 0.2
//Threshold for detecting stillness
#define STILL_THRESHOLD 0.3
class Cord {
  public:
    float X, Y, Z;
};

//Interrupt handler for tap
void tapTime();

//Add a point to the buffer and adjust the sum
Cord addPoint(float X, float Y, float Z);

//Get the current acceleration and update the moving average buffer
Cord getAccel();

//Check the sequence for one of the ten messages
void checkSequence(uint8_t gesture);

#ifdef PREDICT
int predict();

// #define NUM_MODELS 4
//Logistic Regression models for each gesture
// const int16_t upDown[] = {1401, -291, -677, -3165, -3574, -3616, -3594, -2697, -1794, -993, -57, 958, 925, 311, 186, 11, 0, 0, 0, 0, -2902, -582, -1274, 3460, 3123, 1621, 263, 1435, -905, -3246, -5177, -3783, -3071, -128, -52, -15, 0, 0, 0, 0, 5641, 8088, -1670, -3521, -2662, -4017, -3927, -4303, -1020, 1349, 3517, 1210, 1059, 893, -680, -801, 0, 0, 0, 0};
// const float upDownInt = -0.032425486356430784;
// const int16_t downUp[] = {1012, 2232, 2497, 3025, 5089, 7331, 8025, 8577, 1799, 592, -634, -1733, -1310, -915, -384, -2, 0, 0, 0, 0, 2999, -340, 413, 1357, -739, -3451, -5384, -6445, -3227, -2777, -3250, -1145, -670, 334, 111, 3, 0, 0, 0, 0, -2973, -508, 2988, 6921, 1142, -2019, -3428, -1526, -3834, -2202, 31, 349, 659, 236, 42, 184, 0, 0, 0, 0};
// const float downUpInt = -0.14643161539574717;
// const int16_t rightLeft[] = {-2709, -3077, -2879, 75, 234, -82, -89, -867, 728, 629, 289, -113, -555, 21, 6, 0, 0, 0, 0, 0, 5195, 7238, 7466, 1527, 625, 2117, 2943, 877, 1797, 2945, 4646, 3516, 3638, -9, -1, 0, 0, 0, 0, 0, 1167, -611, 2472, 1909, 653, 955, -535, -1251, -1889, -541, -3119, -3006, 398, -2485, -836, -34, 0, 0, 0, 0};
// const float rightLeftInt = -0.026449754090449463;
// const int16_t rotRight[] = {29, 575, 18, -574, -1035, -1377, -1549, -1594, -455, -204, -126, -43, 30, 14, 4, 0, 0, 0, 0, 0, -3017, -4242, -3230, -2115, -1348, -623, 108, 733, 376, 249, 389, 290, -36, -6, -1, 0, 0, 0, 0, 0, -2484, -4753, -3354, -2033, -623, 760, 1495, 2024, 3588, 549, -636, -558, -1689, -577, -182, -37, 0, 0, 0, 0};
// const float rotRightInt = 0.04275485494366888;
const int16_t rightLeft[] = {248, -102, -845, -1620, -2143, -2514, -2663, -2564, -1847, -1766, -1337, -612, -24, 229, 796, 1541, 2263, 2532, 2686, 2154, 5187, 7949, 7567, 5365, 2882, 544, -48, -613, -1433, -2022, -2186, -2292, -3054, -3748, -3341, -4033, -3402, -2840, -747, -1840, 347, 908, 650, 251, -171, -194, -116, -592, 588, 1230, 2389, 2400, 2980, 3045, 3405, 3274, 3617, 3318, 3623, 3866};
const float rightLeftInt = -0.4764453688109578;
const int16_t leftRight[] = {-80, 350, 1079, 1766, 2193, 2546, 2592, 2457, 2094, 2327, 2184, 1722, 1177, 762, 71, -766, -1600, -2139, -2540, -2527, -3241, -4965, -5241, -4131, -2359, -802, -370, -41, 956, 1550, 2031, 2174, 3129, 3924, 4234, 4989, 4782, 4616, 3156, 3682, -160, -636, -662, -405, -286, -132, 46, 503, 163, 335, 119, 565, 678, 964, 975, 994, 684, 859, 633, 384};
const float leftRightInt = 0.3618371859411224;
const int16_t rotRight[] = {-26, -379, -707, -978, -1309, -1772, -2107, -2355, -2482, -2622, -2843, -3138, -3365, -3275, -3044, -2755, -2462, -2083, -1776, -1699, -1005, -1582, -1747, -1707, -1747, -945, -417, 567, 755, 1213, 1340, 1744, 1020, 366, -740, -1177, -1784, -2432, -2511, -2072, 122, 288, 261, 187, 127, 181, 28, 266, -99, -280, -789, -1261, -1947, -2309, -2508, -2308, -2030, -1927, -1904, -1706};
const float rotRightInt = -0.5095718027473871;
const int16_t* models[] = {rightLeft,leftRight,rotRight};
const float modelInts[] = {rightLeftInt,leftRightInt,rotRightInt};
#define NUM_MODELS 3
#endif


// enum Gesture {
//   NONE,
//   RL,
//   LR,
//   RR,
//   CC,
//   TP
// };

// uint8_t sequenceValues_1[10] = {RL, RL, LR, LR, RR, RR, TP, TP, CC, CC};
// uint8_t sequenceValues_2[10] = {RL, LR, RR, TP, CC, RL, LR, RR, TP, CC};

enum Gesture {
  NONE,
  RL,
  LR,
  RR,
  TP
};

uint8_t sequenceValues_1[10] = {RL, RL, RL, LR, LR, LR, RR, RR, RR, TP};
uint8_t sequenceValues_2[10] = {LR, RR, TP, RL, RR, TP, RL, LR, TP, TP};

//Moving average buffer
Cord buffer[BUFF_LEN];
float X, Y, Z;

int end = 0;
//Sum of the buffer
Cord sum = {0.0, 0.0, 0.0};

//Log buffer for gesture recognition
Cord _log[LOG_LEN];
//Index for log buffer
size_t logInd = 0; 

//Basis for gesture recognition
Cord basis = {0.0, 0.0, 0.0};

//Previous point for movement detection
Cord prev = {0.0, 0.0, 0.0};

//Number of still points for detecting stillness
size_t stillCount = 0;

//Counter for skipping frames after a tap
uint8_t skip = 0;

//Sequence buffer
uint8_t sequence[2] = {0,0};
bool seqInd = 0;

volatile bool tapped = false;

enum State {
  WAITING_MOVE,
  LOGGING,
  WAITING_STILL,
  PREDICTING,
  TAPPED
};

State state = WAITING_MOVE;

//Add a point to the buffer and adjust the sum
Cord addPoint(float X, float Y, float Z) {
  Cord tail = buffer[end];
  buffer[end] = {X, Y, Z};

  sum.X += X;
  sum.X -= tail.X;
  sum.Y += Y;
  sum.Y -= tail.Y;
  sum.Z += Z;
  sum.Z -= tail.Z;

  Cord avg = {sum.X/BUFF_LEN, sum.Y/BUFF_LEN, sum.Z/BUFF_LEN};
  end = (end+1) % BUFF_LEN;
  return avg;
}

Cord getAccel() {
  X = CircuitPlayground.motionX();
  Y = CircuitPlayground.motionY();
  Z = CircuitPlayground.motionZ();
  return addPoint(X, Y, Z);
}

#ifdef PREDICT
//Predicts the gesture based on the log. Returns 0 if no gesture
int predict() {
  float sums[NUM_MODELS] = {0.0};
  for (size_t i = 0; i < 20; ++i) {
    for (size_t j = 0; j < NUM_MODELS; ++j) {
      if (!isnan(_log[i].X))
        sums[j] += ((float) (models[j][i]))/10000 * _log[i].X;
    }
  }
  for (size_t i = 20; i < 40; ++i) {
    for (size_t j = 0; j < NUM_MODELS; ++j) {
      if (!isnan(_log[i].Y))
        sums[j] += ((float) (models[j][i]))/10000 * _log[i-20].Y;
    }
  }
  for (size_t i = 40; i < 60; ++i) {
    for (size_t j = 0; j < NUM_MODELS; ++j) {
      if (!isnan(_log[i].Z))
        sums[j] += ((float) (models[j][i]))/10000 * _log[i-40].Z;
    }
  }
  for (size_t i = 0; i < NUM_MODELS; ++i) {
    sums[i] += modelInts[i];
    Serial.print(i);
    Serial.print(": ");
    Serial.print(1 / (1+exp(-sums[i])));
    Serial.print(", ");
  }
  
  Serial.println();
  float max = sums[0];
  int maxInd = 0;
  for (size_t i = 1; i < NUM_MODELS; ++i) {
    if (sums[i] > max) {
      max = sums[i];
      maxInd = i;
    }
  }
  float confidence = 1 / (1+exp(-sums[maxInd]));
  return confidence > 0.8 ? (maxInd+1) : 0;
}
#endif

void tapTime() {
  cli();
  state = TAPPED;
  Serial.println("Tapped");
  sei();
}

void checkSequence(uint8_t gesture) {
    sequence[seqInd] = gesture;
    CircuitPlayground.clearPixels();
    if (seqInd) {
      for (size_t i = 0; i < 10; ++i) {
        if (sequence[0] == sequenceValues_1[i] && sequence[1] == sequenceValues_2[i]) {
          CircuitPlayground.setPixelColor(i, 100, 0, 0);
          break;
        }
      }
    }
    seqInd = (seqInd+1) % 2;
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  CircuitPlayground.begin(); 
  CircuitPlayground.setAccelRange(LIS3DH_RANGE_2_G);
  CircuitPlayground.setAccelTap(2, 100);
  //Clear buffer
  for (int i = 0; i < BUFF_LEN; ++i) {
    buffer[i] = {0.0, 0.0, 0.0};
  }
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
  attachInterrupt(digitalPinToInterrupt(CPLAY_LIS3DH_INTERRUPT), tapTime, FALLING);
}


void loop() {
  Cord avg = getAccel();
  //
  digitalWrite(13, seqInd);
  if (skip > 0) {
    CircuitPlayground.setPixelColor(9, 0,0, max(skip*10, 255));
    --skip;
  } else if (state == WAITING_MOVE) {
    CircuitPlayground.setPixelColor(9, 0, 0, 100);
    //Reset the log
    if (abs(avg.X - prev.X) > MOVEMENT_THRESHOLD || abs(avg.Y - prev.Y) > MOVEMENT_THRESHOLD || abs(avg.Z - prev.Z) > MOVEMENT_THRESHOLD) {
      logInd = 0;
      state = LOGGING;
      basis = prev;
      for (size_t i = 0; i < LOG_LEN; ++i) {
        _log[i] = {0.0, 0.0, 0.0};
      }
    }
  } else if (state == LOGGING) {
    CircuitPlayground.setPixelColor(9, 0, 100, 0);
    _log[logInd] = {avg.X - basis.X, avg.Y - basis.Y, avg.Z - basis.Z};
    ++logInd;
    if (logInd == LOG_LEN) {
      state = WAITING_STILL;
    }
  } else if (state == WAITING_STILL) {
    CircuitPlayground.setPixelColor(9, 100, 0, 0);
    if (stillCount > 10) {
      state = PREDICTING;
      stillCount = 0;
    } else if (abs(avg.X - prev.X) < STILL_THRESHOLD && abs(avg.Y - prev.Y) < STILL_THRESHOLD && abs(avg.Z - prev.Z) < STILL_THRESHOLD) {
      ++stillCount;
    } else {
      stillCount = 0;
    }
  } else if (state == PREDICTING) {
    CircuitPlayground.setPixelColor(9, 100, 100, 0);
    #ifdef PREDICT
    int gesture = predict();
    if (gesture != 0) {
      Serial.print("Gesture: ");
      Serial.println(gesture);
    }
    checkSequence(gesture);
    #endif
    #ifdef STATE
    for (size_t i = 0; i < LOG_LEN; ++i) {
      Serial.print(_log[i].X);
      Serial.print(", ");
    }
    for (size_t i = 0; i < LOG_LEN; ++i) {
      Serial.print(_log[i].Y);
      Serial.print(", ");
    }
    for (size_t i = 0; i < LOG_LEN; ++i) {
      Serial.print(_log[i].Z);
      if (i != LOG_LEN-1)
        Serial.print(", ");
    }
    Serial.println();
    #endif
    #ifdef GRAPH
    for (size_t i = 0; i < LOG_LEN; ++i) {
      Serial.print(_log[i].X);
      Serial.print(", ");
      Serial.print(_log[i].Y);
      Serial.print(", ");
      Serial.println(_log[i].Z);
    }
    #endif
    state = WAITING_MOVE;
    
  } else if (state == TAPPED) {
    state = WAITING_MOVE;
    checkSequence(TP);
    skip = 20;
  }


  delay(50);
  prev = avg;
}

/*
0 - Up Down
1 - Down Up
2 - Right Left
3 - Rotate Right and back

*/