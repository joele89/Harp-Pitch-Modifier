# Pitch Modifier Controller
## Task
Create a physical controller that will let a keyboard player emulate the unique features of a Pedal Harp, in real-time.
## Background
In theatre pits, it’s fairly commonfor synthesizer players to be given the harp book to play. For most of the music, this is straight forward, but harp has some endemic techniques that are hard to duplicate well on a keyboard. These are *glissando* (“glide”) and *bisbiglando* ("whispering"). There are other techniques that do not present significant difficulty to keyboard players, such as dampening (including *secco* and *étouffer*), *pres de la table*, and harmonics.
### Harp Mechanics
The Pedal Harp contains 47 orso strings, and seven pedals. Each of the pedals affects all the strings with the same name; there is one pedal for all the "A" strings, one forall the "B", strings, one for the "C", "D", "E", "F", and "G" strings.

Each pedal can bein three different positions: fiat, natural, and sharp. For example, the "A" pedal can make the "A" strings to be all A&#9837;, all A&#9838;, or all A&#9839;.

A *glissando* is a quick sweep across many of the strings. This is the archetypal harp sound. Depending on the settings of the pedals, very different sounds are produced. Detail is especially important at key-changes, where the harp *glissando* is the mechanism that creates a smoothtransition. (There are 2087 possible pedal combinations, but many of these are redundant. There are about 66 practical combinations). A keyboardis limited to one practical combination, the "white-note gliss".

It's possible for two neighbouring strings to be made to sound at the same pitch, for example F&#9839; and G&#9837;. This allows for easier repeated notes, where the first one is still sounding after the second one is played. This is impossible on a keyboard. *Bisbigliando* uses this technique — quickly and quietly — sometimes extending to multiple pairs, such as E&#9839; & F&#9837;, G&#9839; & A&#9837;, B&#9838; & C&#9837; for a "shimmering" E-major chord.

The normal practice is to set the pedals at the beginning of a piece, then change individual pedals as required, usually in a short gap, or when that pedal’s strings are not being played. It's also possible to change a pedal while one of it's strings is sounding, to give a pitch-bend effect. Keyboards can imitate this effect quite well.

### Order of Pedals
The standard order of harp pedalsis:

  D   C   B   |   E   F   G   A

D-C-B are operated with the left foot, and E-F-G-A are operated with the right foot.

There are two main ways to indicate the pedal positions. The first of these is a harp diagram, used at the start of a piece, or after a significant break for the player. The second is a list of pedal positions, showing all seven pedals, or as few as one pedal. The full list is usually used in places where there is nothing to play, and single pedal lists are often found while the player is playing other strings. Both the diagram and the list are written in the same order as the pedals.

Here are examples of a typical "harp pedal" diagram, and the equivalent "pedal list":

[img]
D&#9837;C&#9839;B&#9837;|E&#9837;F&#9838;G&#9839;A&#9837;

A short list could be "D&#9837;", placed as soon as possible after the last "D&#9838;" or "D&#9839;" was played, and the harpist then changes the "D" pedal to "D&#9837;" while playing other strings.
### Mathematics
In the MIDI system, every note has a value between 0 and 127. The range of the harp is C&#9837;<sub>1</sub>, to G&#9839;<sub>7</sub>, which is MIDI 23 to 104. (The range of a piano is A<sub>0</sub> to C<sub>8</sub> — 21 to 108.)

Each of the named pitches has the same modulo 12 value in MIDI:

   C:0    D:2    E:4    F:5    G:7    A:9    B:11

A flat subtracts 1 from the MIDI value, and a sharp adds 1 to the MIDI value. So it’s easy to see why F&#9839; and G&#9837; have the same sound; they both equal 6 (modulo 12).

If the harp were a MIDI instrument, each pedal would simply add -1, 0, or 1 to the MIDI value of all the strings it affects.
### Keyboard Simulation
The simplest way to emulate *glissando* is to play a white-note gliss. Because all the strings are fixed at "natural", it is rarely effective, and sounds like bad 60s rock.

A better solution is to temporarily transpose (pitch-shift) the whole keyboard into a key where a "white-note gliss" is a better fit. This will need a quick "un-transpose" afterwards, and meansthat there needs to be a small gap in the music before and after the *glissando*. A way around these limitations is to re-typeset a section of music that includes the glissando, and transpose the music to counter the keyboard transposition. Yet, if the pedal combination doesn't match the white-note scale well, the sound will still be unsatisfactory.

The third method — if the keyboard allows it — is to create user-defined scales that match each pedal combination. This takes a lot of preparation time, and might take too much change time in performance. The other difficulty is that the keyboardis likely to have only four storable settings, and definitely no more than sixteen.

It's  possible to combine user-defined scales and keyboard transposition to match more pedal combinations, but this would also need a lot of re-typesetting.

## Physical Operation of the Controller
There should be seven sliders, a "bypass" button, and optionally, a pitch-order control button.
### Sliders
There would need to be seven sliders or levers, each one replicating the actions of a harp pedal.
* Each slider should only affect the notes of it's name — those with the appropriate modulo 12 value.
* Each slider must be able to stay in at least three different positions: top ("flat"), mid ("natural"), and bottom ("sharp").
* Ideally, there should be a "notch" in the middle ("natural") position so that the slider gives tactile feed-back that it’s in the right place.
* If pitch-bend can be included, there should be five zones on the slider. Three of these are: 
  * a small zone at the top which is all "flat",
  * a small zone at the bottom which is all "sharp", and
  * a small zone in the middle which is all "natural".

This gives a little bit of leeway in case the user doesn’t have time to get a change exactly right. 
* The other two zones are:
  * between top and mid, which is a pitch-bend between "flat" and "natural”, and
  * between mid and bottom, which is a pitch-bend between "natural" and "sharp".
* If pitch-bend *cannot* be included, there should only be three zones: top ("flat"), mid ("natural"), and bottom ("sharp").
* Because pedal-changes sometimes need to be made very quickly, each slider must also be able to be moved quickly and firmly, as well as a little in accurately. A physical controller gives immediate feedback and works even if the finger is greasy or damp.
An on-screen slider would be easier to build, but doesn’t give feedback as effectively, and can fail when time is critical. As well as failure to register because of greasy or damp fingers, the screen itself might suddenly "decide" it needs to be touched in a particular way.
### Layoutof Sliders
There should be an obvious grouping of 3 and 4, to match the layout of the harp-pedal diagrams. This could be through a physical separation between the groups, or a visual distinction — a line drawn on the controller, or different colour sliders for the two groups.
### Bypass Button
The bypass button is to let the player quickly switch between "harp alteration" mode and "ordinary keyboard" mode. There are times when it’s easier for the keyboard player to use the white and black keys normally, when there is no need for specific harp techniques.

The bypass button would save the player from having to neutralise all seven sliders to the mid position, and would also save having to restore the setting just before playing a "harp" passage, which will often use the previous setting.

The button should be easy to get to, but not in the way of the sliders. It should stay in the position the player wants, either active or inactive.
### Pitch-Order Switch
This is an optional feature.

Keyboard players are not usually familiar with the standard order of pedals. This could be a problem for a last-minute fill-in player, who has bigger problems than having to learn the "crazy harp order".

The Pitch-Order switch would adjust the order to:

  C   D   E   |   F   G   A   B

Mechanically, this switch would merely change the modulo 12 number associated with each slider. Instead of 2-0-11 | 4-5-7-9, the sliders would be 0-2-4 | 5-7-9-11.

The switch can be out of the way (on a side or the back) as it would only be set once. If it’s in the same location as the sliders and By-pass, it should be small, and hard to change accidentally.
### Labelling
This is probably less important, but — if possible — the two versions should be shown. Maybe the switch could have a small, red light (on for the CDE-FGAB order).
### Physical
The controller should be able to be put onto the playing keyboard. It should be held in place by rubber suction-feet, or something else that cope with a fast, firm touch.
### Connections
The most likely way the controller would be used is through MIDI, from a playing keyboard, through the controller, to a sound generator — either a synth keyboard or a synth module.

The only part of the part of the MIDI signal that should be changed is the pitch. Other facets (such as note-on, note-off, velocity) should be passed throughthe controller unchanged.

Most keyboards can cope with standard 5-pin MIDI, or USB. There are adapters available, and most players would have access to those required for their keyboards.
### Power
It might be possible for the controller to draw power through USB. Otherwise, a standard power source could be used. Keyboard players always have a swarm of power-boards.
