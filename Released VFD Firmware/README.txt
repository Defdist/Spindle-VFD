All steps in this README are shown in the following video:
https://youtu.be/xo_RG4Zgdmc


1: Download and install beta DDcut:
Mac: https://drive.google.com/file/d/1ckqJORKC9LdCiA5aiHUaRxv-CCwtGKTb/view?usp=sharing
Windows: https://drive.google.com/file/d/1EFyPPsjfm5gzKeZ9XufNfWa4SMT3P-wj/view?usp=sharing

2: Open DDcut and go to settings>software

3: Choose the Beta 328p & 32M1 hex files, located in the folder "2022JUN09 beta closed loop" (same directory as this readme).

4: Click "Upload Custom Firmware" button.
DO NOT CLICK THE 'OK' button on the popup message (that says "Upload succeeded == true").   

5: Wait one minute, then click the OK button.

6: Close the settings window, then quit and relaunch DDcut.  This probably isn't necessary, but sometimes I wasn't able to connect to GG without restarting.

7: Open DDcut and go to settings>software.  The 'FW' field should now say '20220609'.

8: Open Manual Control window, then type '$$' to bring up the settings.  Verify the following settings:
-$30 should be 8500
-$31 should be 1360
Please let me know if the old values persist ($30=8000 & $31=0).

9: Home GG, then type:
G0 X0 Y-120
G0 Z-78
M3
S1500

10: Cut existing files and verify everything works well.  Please let me know if you run into problems with any existing code.

11: Cut new things at lower speeds and verify everything works well.

12: If the new closed loop firmware is terrible, you can reload the old version by following the same steps (above), but with the files inside the folder "restore old firmware".