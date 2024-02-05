/*    Test_DFP_Stereo_Lft_Rht_V1B.ino
      Plays to left and right audio channel. Repeatedly.
      For SB_T41_4on_2ext and USER-IO_Stereo boards.
      Plays to amp and speaker or, to earbud if plugged in.
*/

#include <DFPlayerMini_Fast.h>
DFPlayerMini_Fast audioPlayer;

#define HWSERIAL Serial7  // for SB_T41_4on_2ext board

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);     // IDE Serial Monitor

  HWSERIAL.begin(9600); // Teensy 4.1

  audioPlayer.begin(Serial7);  //for SB_4on_2ext_V1

  delay(200);
  audioPlayer.reset();
  delay(200);

  // Volume control

  //audioPlayer.volume(10); // low volume
  //audioPlayer.volume(12); // quiet at two foot distance
  //audioPlayer.volume(14); // good at two foot distance
  //audioPlayer.volume(16); // rectangular spkr comfortable level at two foot distance
  audioPlayer.volume(22); // loud at two foot distance into rectangular spk
  //audioPlayer.volume(30); // sound is broken up, amp is overdriven
}
void loop()
{
  // blink the LED at start of audio
  digitalWrite(LED_BUILTIN, HIGH); delay(200); digitalWrite(LED_BUILTIN, LOW);

  // Use uSD for playing tracks. Can use for playing Lft_Rht.mp3 also.
  Serial.print("Playing Track "); Serial.println(1);
  audioPlayer.play(1); //play  file
  delay(6000);
}
