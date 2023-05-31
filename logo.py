import matplotlib.pyplot as pyplot
import matplotlib.patches as patches
import math
# Set image parameters.
figure, axes = pyplot.subplots(dpi=90, figsize=(8, 4))
axes.set_aspect(1)
pyplot.box(False)
pyplot.xticks([])
pyplot.yticks([])
# Draw the sectors.
draw_circle = patches.Wedge((0, 0.3), 0.3, 210, 330, fill=False, linewidth=0.6, color='#fee4d0')
axes.add_artist(draw_circle)
draw_circle = patches.Wedge((0, -0.3), 0.3, 30, 150, fill=False, linewidth=0.6, color='#fee4d0')
axes.add_artist(draw_circle)
draw_circle = patches.Wedge((math.sqrt(3) * 0.15, 0.15), 0.3, 150, 270, fill=False, linewidth=0.6, color='#fee4d0')
axes.add_artist(draw_circle)
draw_circle = patches.Wedge((math.sqrt(3) * 0.15 * (-1), 0.15), 0.3, 270, 390, fill=False, linewidth=0.6, color='#fee4d0')
axes.add_artist(draw_circle)
draw_circle = patches.Wedge((math.sqrt(3) * 0.15, -0.15), 0.3, 90, 210, fill=False, linewidth=0.6, color='#fee4d0')
axes.add_artist(draw_circle)
draw_circle = patches.Wedge((math.sqrt(3) * 0.15 * (-1), -0.15), 0.3, 330, 450, fill=False, linewidth=0.6, color='#fee4d0')
axes.add_artist(draw_circle)
'''
# Draw the hexagons, unnecessary because patches.Wedge() draws it as well.
pyplot.plot([-0.00039, -0.00039], [-0.3, 0.3], linewidth=0.6, color='#fee4d0')
pyplot.plot([math.sqrt(3) * 0.15, 0], [0.15, 0.3], linewidth=0.6, color='#fee4d0')
pyplot.plot([math.sqrt(3) * 0.15 * (-1), math.sqrt(3) * 0.15 * (-1)], [0.15, -0.15], linewidth=0.6, color='#fee4d0')
pyplot.plot([math.sqrt(3) * 0.15, math.sqrt(3) * 0.15], [0.15, -0.15], linewidth=0.6, color='#fee4d0')
pyplot.plot([math.sqrt(3) * 0.15, 0], [-0.15, -0.3], linewidth=0.6, color='#fee4d0')
pyplot.plot([math.sqrt(3) * 0.15 * (-1), 0], [0.15, 0.3], linewidth=0.6, color='#fee4d0')
pyplot.plot([math.sqrt(3) * 0.15 * (-1), 0], [-0.15, -0.3], linewidth=0.6, color='#fee4d0')
'''
# Draw the diagonals.
pyplot.plot([-0.00044, -0.00044], [-0.3, 0.3], linewidth=0.6, color='#fee4d0')
pyplot.plot([math.sqrt(3) * 0.15 * (-1), math.sqrt(3) * 0.15], [-0.15, 0.15], linewidth=0.6, color='#fee4d0')
pyplot.plot([math.sqrt(3) * 0.15, math.sqrt(3) * 0.15 * (-1)], [-0.15, 0.15], linewidth=0.6, color='#fee4d0')
pyplot.xlim(-0.4, 0.4)
pyplot.ylim(-0.4, 0.4)
# Draw the title.
pyplot.title("r u r i", color='#fee4d0', y=-0.05, x=0.49, fontsize=39, fontweight="ultralight")
pyplot.text(-0.05, -0.12, "Linux containers, simple & secure", fontsize=16,fontweight="ultralight", transform=axes.transAxes, color='#fee4d0')
# Save as logo.png.
pyplot.savefig('logo.png', transparent=True)