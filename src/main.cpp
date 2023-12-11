

#include <Adafruit_CircuitPlayground.h>
#include <Adafruit_Circuit_Playground.h>

#define BUFF_LEN 20
#define LOG_LEN 20
#define STATE
#define ONLY_GRAPH_MOVING

class Cord {
  public:
    float X, Y, Z;
};

#ifdef PREDICT
#define NUM_MODELS 4
//Logistic Regression models for each gesture
const float upDown[] = {0.07521835001394944, 0.06418138181304384, 0.004171434413029203, -0.24663445106896745, -0.30321842318475595, -0.32946247443094057, -0.34064113676632807, -0.26677463697071996, -0.1825706708177661, -0.11550054339554296, -0.026707466669861728, 0.09046032799218562, 0.08441098111026744, 0.030614128654726156, 0.01817047408182008, 0.0012824645036550082, 0.0, 0.0, 0.0, 0.0, 0.01757177918156766, -0.12034629960420128, -0.1740511619188567, 0.2930531571034506, 0.2640047607236051, 0.13257828629869656, 0.012805840848142649, 0.12805169321300625, -0.09901668541725768, -0.31541378120325586, -0.5007909057679588, -0.3803504641372424, -0.2662088445713001, -0.012679750962264272, -0.0050643620617702384, -0.0016956174442267736, 0.0, 0.0, 0.0, 0.0, 0.7845456831239386, 0.6389712775315609, -0.25705932609640764, -0.49471052929615733, -0.348943523105113, -0.4219043232668204, -0.31197979747889704, -0.3514542403393373, -0.07559386320565899, 0.16076224375772397, 0.38502870484861196, 0.13304846722482003, 0.08521100229273688, 0.1135775472914237, -0.05851920447652567, -0.08603837386010386, 0.0, 0.0, 0.0, 0.0};
const float upDownInt = -0.014176514160331619;
const float downUp[] = {0.23542927879342088, 0.343199827120108, 0.37886907189045815, 0.3833713025523684, 0.507717976372813, 0.6258626020901964, 0.6510955611422397, 0.6611155812978231, 0.17320442006679107, 0.04951535878819399, -0.057687227107707725, -0.12983482707365038, -0.0987849012039148, -0.06591032758246669, -0.026955226212184064, -0.00022486284066682076, 0.0, 0.0, 0.0, 0.0, 0.3775947424497268, 0.021084181111635677, -0.03765282590271199, 0.05787489140972208, -0.09022100610832616, -0.3199926387038834, -0.4562462307946727, -0.519435785765467, -0.35376813694542714, -0.3038596957778849, -0.3448156440812159, -0.2199355905912312, -0.053542659228444874, 0.024035138949416692, 0.007814409084826274, 0.00029910372562686773, 0.0, 0.0, 0.0, 0.0, -0.48729721928698544, -0.27552413967375294, 0.0913312571650161, 0.44923168973522676, 0.09224395108917811, -0.08254513098444065, -0.09486236370205647, 0.10349312993802534, -0.2667257547785455, -0.1445025683796652, 0.07333805525439797, 0.12494884305892365, 0.0283501877375598, 0.02839098886400238, 0.034112212697718386, 0.015280106670845327, 0.0, 0.0, 0.0, 0.0};
const float downUpInt = -0.07269614441875487;
const float rightLeft[] = {-0.26803521210771836, -0.3060181369314439, -0.24983070089513032, 0.053046919240563616, 0.07197824455912198, 0.03881146437428015, 0.026734603662124296, -0.05701528264197484, 0.0715366147475333, 0.07325266910072961, 0.023030857165304525, -0.010014733548171825, -0.051010368347473245, 0.002620789348689633, 0.0007833312018849227, 6.890254429770176e-05, 0.0, 0.0, 0.0, 0.0, 0.7097184764386657, 0.8682105907430465, 0.7788444533023683, 0.17571242276380247, 0.05945397750328588, 0.17917925531906237, 0.2294458259479049, 0.02404403018702234, 0.13234760406527363, 0.27773514596822996, 0.4591813903147467, 0.33754986434881307, 0.3544065162524722, -0.0012485055719423524, -0.0001928703234564883, -9.712536823772318e-05, 0.0, 0.0, 0.0, 0.0, 0.10978981575897703, -0.05347870067143846, 0.22927995617935404, 0.14915682373733002, 0.009232512349578509, 0.030285523158730943, -0.12175305685437346, -0.20642258564153443, -0.09186761871965231, 0.05476495370759977, -0.24059473640911005, -0.29396041975375686, 0.04274234564561869, -0.24645342441530207, -0.0800603136269603, -0.005273405574360039, 0.0, 0.0, 0.0, 0.0};
const float rightLeftInt = -0.03672679308885886;
const float rotRight[] = {0.002985005104072975, 0.05750646567670259, 0.001884216786060747, -0.05744371954450454, -0.10351751811053307, -0.13778951622884394, -0.15496608487154795, -0.15947475855798007, -0.045538161838955524, -0.020468471561668207, -0.012614950179248841, -0.004316352170822828, 0.003049307963841031, 0.0014216521006095097, 0.00042028092558966295, 5.137709917002062e-05, 0.0, 0.0, 0.0, 0.0, -0.30178001151491646, -0.42426183587995014, -0.323045599356262, -0.2115282186353547, -0.13484667330014963, -0.06231882721231716, 0.010895409881231536, 0.07335483974128326, 0.03765435761395429, 0.024904063197848877, 0.03898974298704755, 0.029075944483432613, -0.0036099743820962094, -0.0006451695419427535, -0.00014440705202891152, -7.097264171549227e-05, 0.0, 0.0, 0.0, 0.0, -0.2484948431689929, -0.4753679232788697, -0.33545971465066343, -0.20337243653630302, -0.0623744861545512, 0.07603652396727598, 0.14954352810615393, 0.20245488759620658, 0.3588751012076331, 0.054951088532420506, -0.06369458231041653, -0.05582965013676734, -0.16898393315114596, -0.05775876512160965, -0.018284838878240908, -0.0037756177575065317, 0.0, 0.0, 0.0, 0.0};
const float rotRightInt = 0.04275485494366888;
#endif

//Moving average buffer
Cord buffer[BUFF_LEN];
float X, Y, Z;

Cord prev = {0.0, 0.0, 0.0};
bool moving = false;
size_t stillCount = 0;

//Log buffer
Cord _log[LOG_LEN];
size_t logInd = 0; 

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  CircuitPlayground.begin();
  //Clear buffer
  for (int i = 0; i < BUFF_LEN; ++i) {
    buffer[i] = {0.0, 0.0, 0.0};
  }
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
}

int end = 0;
Cord sum = {0.0, 0.0, 0.0};

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


#ifdef PREDICT
//Predicts the gesture based on the log. Returns 0 if no gesture
int predict(Cord cords[]) {
  const float* weights[] = {upDown, downUp, rightLeft, rotRight};
  const float intercepts[] = {upDownInt, downUpInt, rightLeftInt, rotRightInt};
  float sums[] = {0.0, 0.0, 0.0, 0.0};
  for (size_t i = 0; i < 20; ++i) {
    sums[0] += weights[0][i] * cords[i].X;
    sums[1] += weights[1][i] * cords[i].X;
    sums[2] += weights[2][i] * cords[i].X;
    sums[3] += weights[3][i] * cords[i].X;
  }
  for (size_t i = 20; i < 40; ++i) {
    sums[0] += weights[0][i] * cords[i-20].Y;
    sums[1] += weights[1][i] * cords[i-20].Y;
    sums[2] += weights[2][i] * cords[i-20].Y;
    sums[3] += weights[3][i] * cords[i-20].Y;
  }
  for (size_t i = 40; i < 60; ++i) {
    sums[0] += weights[0][i] * cords[i-40].Z;
    sums[1] += weights[1][i] * cords[i-40].Z;
    sums[2] += weights[2][i] * cords[i-40].Z;
    sums[3] += weights[3][i] * cords[i-40].Z;
  }
  for (size_t i = 0; i < NUM_MODELS; ++i) {
    sums[i] += intercepts[i];
  }
  float max = sums[0];
  int maxInd = 0;
  for (size_t i = 0; i < NUM_MODELS; ++i) {
    Serial.print(sums[i]);
    Serial.print("  ");
    if (sums[i] > max) {
      max = sums[i];
      maxInd = i;
    }
  }
  Serial.println();

  return sums[maxInd] > 1.0 ? (maxInd+1) : 0;
}
#endif

void loop() {
  X = CircuitPlayground.motionX();
  Y = CircuitPlayground.motionY();
  Z = CircuitPlayground.motionZ();
  Cord avg = addPoint(X, Y, Z);
  //If total movement is greater than 0.15
  if (avg.X - prev.X + avg.Y - prev.Y + avg.Z - prev.Z > 0.15) {
    if (!moving) {
      //Start moving
      moving = true;
      stillCount = 0;
    } else {
      //Continue moving, reset still counter
      stillCount = 0;
      //If the log is not full, add the point to the log
      if (logInd < LOG_LEN) {
        _log[logInd] = avg;
        logInd++;
      }
    }
  } else if (moving) {
    //If we are moving and the movement is less than 0.15, increment still counter
    stillCount++;
    if (stillCount > 20) {
      moving = false;
    #ifdef STATE
      for (int i = 0; i < 20; ++i) {
        Serial.print(_log[i].X);
        Serial.print(", ");
      }
      Serial.println();
      for (int i = 0; i < 20; ++i) {
        Serial.print(_log[i].Y);
        Serial.print(", ");
      }
      Serial.println();
      for (int i = 0; i < 20; ++i) {
        Serial.print(_log[i].Z);
        Serial.print(", ");
      }
      Serial.println();
    #endif

    #ifdef PREDICT
      //Predict the gesture
      digitalWrite(13, HIGH);
      int pred = predict(_log);
      digitalWrite(13, LOW);
      Serial.println(pred);
      //Light up the neopixel corresponding to the gesture
      CircuitPlayground.clearPixels();
      if (pred != 0) {
        CircuitPlayground.setPixelColor(pred-1, 255, 0, 0);
      }
      //Here because I think I somehow fried my neopixels
      for (int i = 0; i < pred; i++) {
        digitalWrite(13, HIGH);
        delay(50);
        digitalWrite(13, LOW);
        delay(50);
      }
  #endif
      //Clear the log
      for (size_t i = 0; i < logInd; ++i) {
        _log[i] = {0.0, 0.0, 0.0};
      }
      logInd = 0;
    }
  }
  prev = avg;
  delay(50);
}

/*
0 - Up Down
1 - Down Up
2 - Right Left
3 - Rotate Right and back

*/