# De_Castlejau_Algorithm_Bieser_Curve
OpenGL implementation of Bezier Curve
Problem: We would like to make an editable Bezier curve.<br><br>
## Task 1: Implement the de Castlejau algorithm for evaluating the entire 2D Bezier curve of degree n. [2]<br><br>
## Task 2: Make your curve editable in the following sense: [2+2+2]<br><br>
### Addition of control Point: Every time we click on the canvas, a new point will be created and a new Bezier curve of appropriate degree (based on the number of points) will be redrawn.
### Deletion of control point: We can delete an already existing control point and redraw the new Bezier curve of appropriate degree.
### Control Point Movement: An user can drag any control point of the curve and correspondingly the curve should get update automatically

# FreeGlut Implementation.
### The "Bieser Curve.rar" file has the Visual Studio 2019 Solution File with all the Libraries Linked.
The Project has the Following Functionality.
Press Left Mouse Button to add point
Press Middle(Scroll) Mouse Button to drag the nearest point to a new location
Press Right Mouse Button to Remove the nearest point.

### Our curve (4 point Bezier Curve made by clicking on the respective points)
![alt text](https://github.com/siddsh/De_Castlejau_Algorithm_Bieser_Curve/blob/master/resources/image.png)

### Add point by clicking the left mouse button 
![alt text](https://github.com/siddsh/De_Castlejau_Algorithm_Bieser_Curve/blob/master/resources/image(1).png)

### Remove the point nearest to cursor by clicking the right mouse button (Removed the first Point) 
![alt text](https://github.com/siddsh/De_Castlejau_Algorithm_Bieser_Curve/blob/master/resources/image(2).png)

### Move the point nearest to cursor by clicking the scroll button (Shifted the position of the last point, Bottom Left)
![alt text](https://github.com/siddsh/De_Castlejau_Algorithm_Bieser_Curve/blob/master/resources/image(3).png)
