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
tim/gameover.tim \
tim/FAM.tim \
tim/SAM.tim \
tim/fnt.tim \
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
