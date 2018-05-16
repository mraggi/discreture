combinationBF = [0.0150758, 0.01181, 0.022085, 0.0456562, 0.0859039, 0.177223, 0.32892, 0.652955, 1.24239, ]
combinations = [0.0108466, 0.0221961, 0.0416803, 0.0846494, 0.161391, 0.323459, 0.627338, 1.25754, 2.45626, ]
euler314 = [0.0143413, 0.0295464, 0.0569255, 0.114605, 0.223078, 0.44823, 0.844459, 1.74143, 3.23754, ]
combinations_reversed = [0.0209183, 0.0418861, 0.0789569, 0.161724, 0.307578, 0.626626, 1.19281, 2.48539, 4.64448, ]
combinations_tree = [0.0177809, 0.0344807, 0.060538, 0.125613, 0.23688, 0.482461, 0.91294, 1.89001, 3.60567, ]
combinations_tree_reversed = [0.0144773, 0.0302511, 0.0572996, 0.11488, 0.218862, 0.453409, 0.844814, 1.75308, 3.33532, ]
gsl = [0.0268195, 0.0534485, 0.101359, 0.206594, 0.395521, 0.7995, 1.52672, 3.11631, 5.96665, ]

n = len(combinations)

start = 25

comb = [(i+start,combinations[i]) for i in range(n)]
tcomb = [(i+start,combinations_tree[i]) for i in range(n)]
trcomb = [(i+start,combinations_tree_reversed[i]) for i in range(n)]
rcomb = [(i+start,combinations_reversed[i]) for i in range(n)]
gcomb = [(i+start,gsl[i]) for i in range(n)]
E = [(i+start,euler314[i]) for i in range(n)]
#EM = [(i+start,euler314maximin[i]) for i in range(n)]
BF = [(i+start,combinationBF[i]) for i in range(n)]

P =  line(gcomb, color = "green",thickness=1,legend_label="GNU Scientific Library",legend_color="green") 
P += line(trcomb,color="cyan",thickness=1,legend_label="Discreture Reverse Tree",legend_color="cyan")
P += line(E,color="yellow",thickness=1,legend_label="euler314's library",legend_color="yellow")
P += line(tcomb,color="magenta",thickness=1,legend_label="Discreture Tree",legend_color="magenta")
P += line(rcomb,color="red",thickness=1,legend_label="Discreture Reverse",legend_color="red")
#P += line(EM,color="gray",thickness=1,legend_label="euler314's with discreture's commit",legend_color="gray")
P += line(comb,thickness=1,legend_label="Discreture",legend_color="blue") 
P += line(BF,color="black",thickness=1,legend_label="Discreture for_each",legend_color="black")

P += sum([point2d(c,size=20,color="green") for c in gcomb])
P += sum([point2d(c,size=20,color="cyan") for c in trcomb])
P += sum([point2d(c,size=20,color="yellow") for c in E])
P += sum([point2d(c,size=20,color="magenta") for c in tcomb])
P += sum([point2d(c,size=20,color="red") for c in rcomb])
P += sum([point2d(c,size=20,color="blue") for c in comb])
#P += sum([point2d(c,size=20,color="gray") for c in EM])
P += sum([point2d(c,size=20,color="black") for c in BF])

P.show(dpi=200,axes_labels=("$n$", "seconds"),fontsize=12,show_legend=True,axes_labels_size=1.5)

P.save("/home/mraggi/Dropbox/sources/Mathematics/discreture/combvsgsl.png",dpi=200)
