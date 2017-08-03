from scipy import misc
import matplotlib.pyplot as plt

blank = misc.imread("trainingb.png")
troop = misc.imread("trainingt.png")
troop2 = misc.imread("trainingt2.png")
res = troop-blank
res2 = troop2-blank
plt.figure()
plt.imshow(troop)
plt.figure()
plt.imshow(troop2)
plt.figure()
plt.imshow(res)
plt.figure()
plt.imshow(res2)
plt.show()
