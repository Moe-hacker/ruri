'''
  SPDX-License-Identifier: MIT
  This file is part of ruri.
  MIT License
 
  Copyright (c) 2022-2023 Moe-hacker
 
  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:
 
  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
 
  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.
'''
import matplotlib.pyplot as pyplot
import matplotlib.patches as patches
import math
import sys
if len(sys.argv)>1:
    if sys.argv[1]=="-n":
        no_text=True
    else:
        print("Usage: logo.py <-n>")
        exit(1)
else:
    no_text=False
# Set image parameters.
if no_text==False:
    figure, axes = pyplot.subplots(dpi=200, figsize=(8, 4))
    pyplot.box(False)
    pyplot.xticks([])
    pyplot.yticks([])
    pyplot.subplots_adjust(bottom=0.2,top=1)
else:
    figure, axes = pyplot.subplots(dpi=128, figsize=(4, 4))
    axes.set_axis_off()
    #figure.set_size_inches((4,4))
    pyplot.subplots_adjust(left=0,bottom=0,right=1,top=1)
axes.set_aspect(1)
# Draw the sectors.
draw_circle = patches.Wedge((0, 6), 6, 210, 330, fill=False, linewidth=1.5, color='#fee4d0')
axes.add_artist(draw_circle)
draw_circle = patches.Wedge((0, -6), 6, 30, 150, fill=False, linewidth=1.5, color='#fee4d0')
axes.add_artist(draw_circle)
draw_circle = patches.Wedge((math.sqrt(3) * 3, 3), 6, 150, 270, fill=False, linewidth=1.5, color='#fee4d0')
axes.add_artist(draw_circle)
draw_circle = patches.Wedge((math.sqrt(3) * 3 * (-1), 3), 6, 270, 390, fill=False, linewidth=1.5, color='#fee4d0')
axes.add_artist(draw_circle)
draw_circle = patches.Wedge((math.sqrt(3) * 3, -3), 6, 90, 210, fill=False, linewidth=1.5, color='#fee4d0')
axes.add_artist(draw_circle)
draw_circle = patches.Wedge((math.sqrt(3) * 3 * (-1), -3), 6, 330, 450, fill=False, linewidth=1.5, color='#fee4d0')
axes.add_artist(draw_circle)
'''
# Draw the hexagons, unnecessary because patches.Wedge() draws it as well.
pyplot.plot([-0.00039, -0.00039], [-6, 6], linewidth=1.5, color='#fee4d0')
pyplot.plot([math.sqrt(3) * 3, 0], [3, 6], linewidth=1.5, color='#fee4d0')
pyplot.plot([math.sqrt(3) * 3 * (-1), math.sqrt(3) * 3 * (-1)], [3, -3], linewidth=1.5, color='#fee4d0')
pyplot.plot([math.sqrt(3) * 3, math.sqrt(3) * 3], [3, -3], linewidth=1.5, color='#fee4d0')
pyplot.plot([math.sqrt(3) * 3, 0], [-3, -6], linewidth=1.5, color='#fee4d0')
pyplot.plot([math.sqrt(3) * 3 * (-1), 0], [3, 6], linewidth=1.5, color='#fee4d0')
pyplot.plot([math.sqrt(3) * 3 * (-1), 0], [-3, -6], linewidth=1.5, color='#fee4d0')
'''
# Draw the diagonals.
if no_text==False:
    pyplot.plot([-0.003, -0.003], [-6, 6], linewidth=1.5, color='#fee4d0')
else:
    pyplot.plot([0, 0], [-6, 6], linewidth=1.5, color='#fee4d0')
pyplot.plot([math.sqrt(3) * 3 * (-1), math.sqrt(3) * 3], [-3, 3], linewidth=1.5, color='#fee4d0')
pyplot.plot([math.sqrt(3) * 3, math.sqrt(3) * 3 * (-1)], [-3, 3], linewidth=1.5, color='#fee4d0')
if no_text==False:
    pyplot.xlim(-8, 8)
    pyplot.ylim(-8, 8)
else:
    pyplot.xlim(-6.3, 6.3)
    pyplot.ylim(-6.3, 6.3)
# Draw the title.
if no_text==False:
    pyplot.title("r u r i", color='#fee4d0', y=-0.05, x=0.475, fontsize=39, fontweight="normal")
    pyplot.text(-0.12, -0.12, "Linux containers, simple & secure", fontsize=16,fontweight="black", transform=axes.transAxes, color='#fee4d0')
    # Save as logo.png.
    pyplot.savefig('logo.png', transparent=True)
else:
    # Save as logo.svg.
    pyplot.savefig('logo.svg', transparent=True)