.PHONY: all cleansub
all:
	mkpsxiso -y ./isoconfig.xml
cleansub:
	$(MAKE) clean
	rm -f game.cue game.bin

TARGET = game

SRCS = game.c \
tim/officeLEFT.tim \
tim/officeLEFTlight.tim \
tim/officeLEFTnolight.tim \
tim/officeLEFTlightbonnie.tim \
tim/officeMIDDLE.tim \
tim/officeMIDDLEnolight.tim \
tim/officeRIGHT.tim \
tim/officeRIGHTlight.tim \
tim/officeRIGHTlightchica.tim \
tim/officeRIGHTnolight.tim \
tim/CAMERAMONITOR.tim \
tim/freddysneak.tim \
tim/FAM.tim \
tim/load.tim \
tim/SAM.tim \
tim/fnt.tim \
tim/GJFIV.tim \
tim/GJSEV.tim \
tim/GJSIX.tim \
tim/doors.tim \
tim/jumpC.tim \
tim/jumpC2.tim \
tim/jumpC3.tim \
tim/jumpB.tim \
tim/jumpB2.tim \
tim/jumpB3.tim \
tim/jumpF.tim \
tim/jumpF2.tim \
tim/jumpF3.tim \
tim/jumpF20.tim \
tim/jumpF21.tim \
tim/jumpF22.tim \
tim/jumpF24.tim \
tim/jumpF25.tim \
tim/jumpFO.tim \
tim/jumpFO2.tim \
tim/jumpFO3.tim \
tim/static1.tim \
tim/itsme.tim \
vag/Door.vag \
vag/light.vag \
vag/Monitor.vag \
vag/officesound.vag \
vag/click.vag \
vag/noisedoor.vag \
vag/screamer.vag \
vag/honk.vag \
vag/Footstep.vag \
vag/knock.vag \
vag/footstepfoxy.vag \
vag/lightout.vag \
vag/jamlight.vag \
vag/footstep2.vag\

include ../common.mk 
