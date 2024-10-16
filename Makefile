.PHONY: all cleansub
all:
	mkpsxiso -y ./isoconfig.xml
cleansub:
	$(MAKE) clean
	rm -f game.cue game.bin

TARGET = game

SRCS = game.c \
tim/office/officeLEFT.tim \
tim/office/officeLEFTlight.tim \
tim/office/officeLEFTnolight.tim \
tim/office/officeLEFTlightbonnie.tim \
tim/office/officeMIDDLE.tim \
tim/office/officeMIDDLEnolight.tim \
tim/office/officeRIGHT.tim \
tim/office/officeRIGHTlight.tim \
tim/office/officeRIGHTlightchica.tim \
tim/office/officeRIGHTnolight.tim \
tim/office/mutecall.tim \
tim/FAM.tim \
tim/load.tim \
tim/SAM.tim \
tim/AM.tim \
tim/fnt.tim \
tim/GJSEV.tim \
tim/GJSIX.tim \
tim/screamers/jumpC.tim \
tim/screamers/jumpC2.tim \
tim/screamers/jumpC3.tim \
tim/screamers/jumpC4.tim \
tim/screamers/jumpC5.tim \
tim/screamers/jumpB.tim \
tim/screamers/jumpB2.tim \
tim/screamers/jumpB3.tim \
tim/screamers/jumpB4.tim \
tim/screamers/jumpB5.tim \
tim/screamers/jumpB6.tim \
tim/screamers/jumpB7.tim \
tim/screamers/jumpF.tim \
tim/screamers/jumpF2.tim \
tim/screamers/jumpF3.tim \
tim/screamers/jumpF4.tim \
tim/screamers/jumpF5.tim \
tim/screamers/jumpF6.tim \
tim/screamers/jumpF7.tim \
tim/screamers/jumpF20.tim \
tim/screamers/jumpF21.tim \
tim/screamers/jumpF22.tim \
tim/screamers/jumpF24.tim \
tim/screamers/jumpF25.tim \
tim/screamers/jumpF26.tim \
tim/screamers/jumpFO.tim \
tim/screamers/jumpFO2.tim \
tim/screamers/jumpFO3.tim \
tim/screamers/jumpFO4.tim \
tim/screamers/jumpFO5.tim \
tim/itsme.tim \
tim/rect.tim \
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
