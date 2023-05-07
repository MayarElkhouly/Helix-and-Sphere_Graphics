# Helix-and-Sphere_Graphics
You are required to create an OpenGL project using the project template. You should implement an application
that asks user to choose between two types of shapes (Helix and Sphere).
Circular helix parametric equation:
X(t) = Xc + R * cos(t)
Y(t) = Yc + R * sin(t)
Z(t) = P * t
Where Xc, Yc center of the helix, R is radius of the helix and P is the pitch of helix (the height of one complete helix turn).
You should choose Xc, Yc such that helix appears fully within application window.
At runtime, Input handling should be as follows:
• In case of sphere:
o When user presses Q/q, increase/decrease number of latitudinal slices.
o When user presses P/p, increase/decrease number of longitudinal slices.
o When user presses W/w, draw sphere in wireframe / draw filled sphere.
• In case of helix:
o When user presses R/r, increase/decrease radius of the helix
o When user presses H/h, increase/decrease pitch of helix.
o When user presses N/n, increase/decrease number of vertices used to draw the helix.
