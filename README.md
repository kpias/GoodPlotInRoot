# GoodPlotForRoot

This project aims at improving the readability and esthetics of plots in ROOT 
analysis framework, at a 'basic' level: general plots and phase space distributions.
It's been made for CBM [1] users, but could be of interest for RHIC community.

To download it, in terminal type:
$ git clone https://github.com/kpias/GoodPlotInRoot.git

The slides in pdf are in this file: k.piasecki_good_plot_root.pdf

Slides are accompanied with macros ( runnable via root -l myMacro.C ) :
o [General plots] : firstPlot.C , plot_v?.C
o [Pt - Y  plots] : pty_plot.C , pty_plot_v2.C
                    ⤷ they load the input data, phqmd_auau3.25GeV_*.root

[1] www.cbm.gsi.de
