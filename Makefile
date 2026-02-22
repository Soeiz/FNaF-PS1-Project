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
tim/office/officeRIGHTnolight.tim \
tim/office/text/powerleft.tim \
tim/office/text/usage.tim \
tim/office/text/usagebars.tim \
tim/office/text/night.tim \
tim/office/text/nightsnumber.tim \
tim/office/mutecall.tim \
tim/office/fan/1.tim \
tim/office/fan/2.tim \
tim/office/fan/3.tim \
tim/AM/office/1.tim \
tim/AM/office/2.tim \
tim/AM/office/3.tim \
tim/AM/office/4.tim \
tim/AM/office/5.tim \
tim/AM/office/12.tim \
tim/office/littlechica.tim \
tim/AM/FAM.tim \
tim/AM/SAM.tim \
tim/AM/AM.tim \
tim/load.tim \
tim/fnt.tim \
tim/GJSEV.tim \
tim/GJSIX.tim \
tim/menus/WARNING.tim \
tim/menus/STATIC.tim \
tim/menus/lines/1.tim \
tim/menus/lines/2.tim \
tim/menus/lines/3.tim \
tim/menus/lines/4.tim \
tim/menus/lines/5.tim \
tim/menus/night/1ST.tim \
tim/menus/night/2ND.tim \
tim/menus/night/3RD.tim \
tim/menus/night/4TH.tim \
tim/menus/night/5TH.tim \
tim/menus/night/6TH.tim \
tim/menus/night/7TH.tim \
tim/menus/night/NIGHT.tim \
tim/menus/star.tim \
tim/screamers/jumpC.tim \
tim/screamers/jumpC2.tim \
tim/screamers/jumpC3.tim \
tim/screamers/jumpC4.tim \
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
vag/freddy1short.vag \
vag/freddy2short.vag\
vag/CameraGlitching.vag\

include ../common.mk 
