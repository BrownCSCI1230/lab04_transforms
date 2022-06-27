# Lab 4: Transforms

[GitHub Classroom assignment](https://google.com)

## 0. Intro

The purpose of this lab is to help you get more comfortable with 2D and 3D transformations and coordinate spaces. Through this lab we want you to understand how to construct transformation matrices and apply them to modify objects in your scene. You will also use transformations to move between the different coordinate spaces used in building your raytracer.

During this lab you will learn how to:

1. Construct individual matrices that represent **scaling**, **rotating**, and **translating** transformations.
2. Compose multiple transformations to obtain a cumulative transformation.
3. Construct a view matrix representing a specific camera transformation.
4. Use **model** and **view** matrices to transition between **object space**, **world space**, and **camera space**.

## 1. Constructing Transformations

### 1.1 Representing Transformations as Matrices

A transformation can be thought of as a function.

Given an input vertex $v$, we can apply a linear transformation $T$ to produce a new output vertex $T(v)=v'$. Linear transformations are one-to-one, with each input vertex only having one transformed output, so we can represent this transformation $T$ as a matrix $M$. Applying the transformation is just multiplying $v$ by the transformation matrix: $Mv=v'$.

Therefore, we can represent our transformation as such in 2D:

$$ T(v) = Mv = \begin{bmatrix} a && b \\\ c && d \end{bmatrix} \begin{bmatrix} x \\\ y \end{bmatrix} = \begin{bmatrix} ax + by \\\ cx + dy \end{bmatrix} = \begin{bmatrix} x' \\\ y' \end{bmatrix} = v' $$

Similarly in 3D:

$$ T(v) = Mv = \begin{bmatrix} a && b && c \\\ d && e && f \\\ g && h && i \end{bmatrix} \begin{bmatrix} x \\\ y \\\ z \end{bmatrix} = \begin{bmatrix} ax + by + cz \\\ dx + ey + fz \\\ gx + hy + iz \end{bmatrix} = \begin{bmatrix} x' \\\ y' \\\ z' \end{bmatrix} = v' $$

> Keep in mind that this is only a limited representation of transformations! As we will see later on, we will need to expand our definition of a transformation matrix to be able to accommodate all of the types of transformations we want to use.

Like any one-to-one function, we can reverse a transformation by multiplying by the inverse of the associated matrix.

$$ T(v) = Mv = v' $$

$$ v = M^{-1}v' $$

### 1.2 Scaling

We learned about a few common transformations in class, the simplest being scaling. To scale $x$ by $s_x$ and $y$ by $s_y$, we want to transform our standard basis vectors $e_1 = \begin{bmatrix} 1 \\\ 0 \end{bmatrix}$ and $e_2 = \begin{bmatrix} 0 \\\ 1 \end{bmatrix}$ into 
$\begin{bmatrix} s_x \\\ 0 \end{bmatrix}$ and $\begin{bmatrix} 0 \\\ s_y \end{bmatrix}$.

<details>
<summary>A refresher on basis vectors</summary>
  
<b>TODO: make this description better. Cut down to just what is essential for transformations. Maybe even cut out whole mention of bases entirely and try to explain without diving too deep into linalg</b>

If you’ve taken linear algebra before you might be familiar with basis vectors. If not, here’s the basis of it. Ha. Haha.

Think about our regular 3D coordinate system. We can define any point using a set of units along each axis to the position (x, y, z). If we think of our axes as being lines defined by 3 unit length vectors, then our coordinates are just the factors by which we multiply each of those unit vectors by, then sum, to get the resulting position. 

![](basis.png)

The basis vectors are the vectors that define a coordinate system. Our standard basis are these unit vectors that define our default axes: $\begin{bmatrix} 1 \\\ 0 \\\ 0 \end{bmatrix}$,
$\begin{bmatrix} 0 \\\ 1 \\\ 0 \end{bmatrix}$, and $\begin{bmatrix} 0 \\\ 0 \\\ 1 \end{bmatrix}$. When we multiply our transformation matrices, we transform these basis vectors to a new basis that defines a new coordinate system (more on different coordinates later in the lab).

What’s important to take away from all of this is that knowing how the standard basis vectors should end up being transformed makes it very easy to construct the transformation matrix. <b>In between step here.</b> Our transformation matrix is just made up of our new basis vectors as columns.

</details>

We can construct the transformation matrix using these basis vectors to apply the transformation as such

$$ \begin{bmatrix} s_x && 0 \\\ 0 && s_y \end{bmatrix}
\begin{bmatrix} x \\\ y \end{bmatrix} =
\begin{bmatrix} s_xx + 0y \\\ 0x + s_yy \end{bmatrix} =
\begin{bmatrix} s_xx \\\ s_yy \end{bmatrix} $$

Or in 3D:

$$ \begin{bmatrix} s_x && 0 && 0 \\\ 0 && s_y && 0 \\\ 0 && 0 && s_z \end{bmatrix}
\begin{bmatrix} x \\\ y \\\ z \end{bmatrix} =
\begin{bmatrix} s_xx + 0y + 0z \\\ 0x + s_yy + 0z \\\ 0x + 0y + s_zz \end{bmatrix} =
\begin{bmatrix} s_xx \\\ s_yy \\\ s_zz \end{bmatrix} $$

![](scaling.gif)

$$ \begin{bmatrix} 2 && 0 \\\ 0 && 2 \end{bmatrix}
\begin{bmatrix} x \\\ y \end{bmatrix} =
\begin{bmatrix} s_xx + 0y \\\ 0x + s_yy \end{bmatrix} =
\begin{bmatrix} 2x \\\ 2y \end{bmatrix} $$


### 1.3 Rotation

Rotation in 2D follows a similar idea as scaling. We want to take our standard basis vectors and find the transformed basis vectors. Rotating $e_1$ around the origin by
$\theta$ results in $\begin{bmatrix} \cos\theta \\\ \sin\theta \end{bmatrix}$.
$e_2$ becomes $\begin{bmatrix} -\sin\theta \\\ \cos\theta \end{bmatrix}$.

$$ \begin{bmatrix} \cos\theta && -\sin\theta \\\ \sin\theta && \cos\theta \end{bmatrix}
\begin{bmatrix} x \\\ y \end{bmatrix} =
\begin{bmatrix} x\cos\theta - y\sin\theta \\\ x\sin\theta + y\cos\theta \end{bmatrix} $$

![](rotating.gif)

$$ \begin{bmatrix} \cos\frac{\pi}{6} && -\sin\frac{\pi}{6} \\\ \sin\frac{\pi}{6} && \cos\frac{\pi}{6} \end{bmatrix}
\begin{bmatrix} x \\\ y \end{bmatrix} =
\begin{bmatrix} x\cos\frac{\pi}{6} - y\sin\frac{\pi}{6} \\\ x\sin\frac{\pi}{6} + y\cos\frac{\pi}{6} \end{bmatrix} $$

In 3D, this is a bit more complex. Rather than always rotating about the origin in a fixed and consistent way, 3D allows for rotation around any arbitrary axis. There are many ways to handle this (as covered during the lectures), but for now we'll use the axis-aligned **Euler angles** approach as this is the simplest for constructing your own matrices. For this, we define the rotation about each standard axis independently, and then compose them. We use $R_n$ to notate the rotation matrix about the $n$-axis.

$$ R_x = \begin{bmatrix} 1 && 0 && 0 \\\ 0 && \cos\theta && \sin\theta \\\ 0 && -\sin\theta && \cos\theta \end{bmatrix} $$

$$ R_y = \begin{bmatrix} \cos\theta && 0 && -\sin\theta \\\ 0 && 1 && 0 \\\ \sin\theta && 0 && \cos\theta \end{bmatrix} $$

$$ R_z = \begin{bmatrix} \cos\theta && \sin\theta && 0 \\\ -\sin\theta && \cos\theta && 0 \\\ 0 && 0 && 1 \end{bmatrix} $$

When you want to rotate about multiple axes, you have to compose multiple of these individual transformations. We'll discuss the composition of transformations a bit more later, but just keep in mind that there are different orders in which you can apply the rotations. One common standard is to do the $x$-axis first, then the $y$-axis, then the $z$-axis.

$$ combined = R_z R_y R_x $$

### 1.4 Translation

Translation is where our previous understanding of transformation matrices stops working. Until now, we have only been working with **linear transformations**. These transformations always preserve the origin, meaning that multiplying the corresponding transformation matrix by $\begin{bmatrix} 0 \\\ 0 \end{bmatrix}$ will always produce the same point,
$\begin{bmatrix} 0 \\\ 0 \end{bmatrix}$.

Translation, on the other hand, is an **[affine transformation](https://en.wikipedia.org/wiki/Affine_transformation)**. Unlike linear transformations, affine transformations do not need to preserve the origin. All linear transformations are affine transformations, but some affine transformations are not linear like translation.

![](transformtypes.png)

This affects our representation of transformations as matrices because a 2x2 matrix is no longer sufficient for transforming a 2x1 point in this way.\:

$$ \begin{bmatrix} a && b \\\ c && d \end{bmatrix} \begin{bmatrix} 0 \\\ 0 \end{bmatrix} = \begin{bmatrix} 0a + 0b \\\ 0c + 0d \end{bmatrix} = \begin{bmatrix} 0 \\\ 0 \end{bmatrix} $$

As you can see, there is no possible 2x2 matrix that could translate the 2x1 origin. No matter what values we fill in the matrix, they will be multiplied by 0 when transforming the origin, resulting in the same point $\begin{bmatrix} 0 \\\ 0 \end{bmatrix}$ limiting us to strictly linear transformations. To represent our desired non-linear transformation as a matrix, we introduce **homogeneous coordinates**.

#### 1.4.1 Homogeneous Coordinates

Homogeneous coordinates are pretty simple to _use_, though they might be difficult to understand. The idea is that we take our existing point or vector and just add another dimension. By convention we refer to this new coordinate as $w$. For points, $w=1$ and for vectors $w=0$.

So in 2D, points become $\begin{bmatrix} x \\\ y \\\ 1 \end{bmatrix}$ and vectors become
$\begin{bmatrix} x \\\ y \\\ 0 \end{bmatrix}$.

In 3D we use $\begin{bmatrix} x \\\ y \\\ z \\\ 1 \end{bmatrix}$ and
$\begin{bmatrix} x \\\ y \\\ z \\\ 0 \end{bmatrix}$.

Correspondingly, we must also enlarge our transformation matrix. In 2D, our matrix becomes 3x3 and in 3D, it becomes 4x4.

<details>
<summary>A refresher on points vs. vectors</summary>
<b>TODO</b>
</details>

<details>
<summary>How does this affect what we've learned so far?</summary>

First off, adding the extra dimension does not break how points and vectors work.

point + vector = point $(1 + 0 = 1)$

point - point = vector $(1 - 1 = 0)$

any operations between vectors (addition $0 + 0$, subtraction $0 - 0$, dot product $0 * 0$) = vector (0)

To modify our previous linear transformations to be compatible with our new matrix size for translation, we simply add another dimension with 0s for all the values except for a 1 along the diagonal like this:
  
$$ \begin{bmatrix} s_x && 0 && 0 \\\ 0 && s_y && 0 \\\ 0 && 0 && 1 \end{bmatrix}
\begin{bmatrix} x \\\ y \\\ 1 \end{bmatrix} =
\begin{bmatrix} s_xx + 0y + 0 * 1 \\\ 0x + s_yy + 0 * 1 \\\ 0 * 0 + 0 * 0 + 1 * 1 \end{bmatrix} =
\begin{bmatrix} s_xx \\\ s_yy \\\ 1 \end{bmatrix} $$

Note how our new extended portion of the matrix resembles the identity matrix because we do not want the conversion to the homogeneous matrix to change what the transformation does!

</details>

We use this extra dimension to insert our translation values. Here $d_x$, $d_y$, and $d_z$ are the amounts translated along each axis.

$$ \begin{bmatrix} 1 && 0 && d_x \\\ 0 && 1 && d_y \\\ 0 && 0 && 1 \end{bmatrix}
\text{or}
\begin{bmatrix} 1 && 0 && 0 && d_x \\\ 0 && 1 && 0 && d_y \\\ 0 && 0 && 1 && d_z \\\ 0 && 0 && 0 && 1 \end{bmatrix} $$

$$ \begin{bmatrix} 1 && 0 && 0 && d_x \\\ 0 && 1 && 0 && d_y \\\ 0 && 0 && 1 && d_z \\\ 0 && 0 && 0 && 1 \end{bmatrix}
\begin{bmatrix} x \\\ y \\\ z \\\ 1 \end{bmatrix} = 
\begin{bmatrix} x + d_x \\\ y + d_y \\\ z + d_z \\\ 1 \end{bmatrix} $$

See how adding the $w$ coordinate allows us to apply the translation using matrix multiplication? Additionally, translation works here on a point because $w=1$. We don't want vectors to be translated because they don't have a location. Vectors represent the difference between two points, defined by having a length and a direction. Neither of these attributes should change with translation, because shifting two points maintains the same displacement between them.

![](vectortranslation.png)

Homogeneous coordinates account for this difference between how points and vectors should be transformed. Since $w=0$ for vectors, if we try to translate a vector, we will just end up with the same vector because the translation coordinates are placed in the last column of the matrix which gets multiplied by the $w$ coordinate of the vector:

$$ \begin{bmatrix} 1 && 0 && 0 && d_x \\\ 0 && 1 && 0 && d_y \\\ 0 && 0 && 1 && d_z \\\ 0 && 0 && 0 && 1 \end{bmatrix}
\begin{bmatrix} x \\\ y \\\ z \\\ 0 \end{bmatrix} = 
\begin{bmatrix} x \\\ y \\\ z \\\ 0 \end{bmatrix} $$

![](translating.gif)

$$ \begin{bmatrix} 1 && 0 && 1 \\\ 0 && 1 && 1 \\\ 0 && 0 && 1 \end{bmatrix}
\begin{bmatrix} x \\\ y \\\ 1 \end{bmatrix}
\begin{bmatrix} x + 1 \\\ y + 1 \\\ 1 \end{bmatrix}$$

## 2. Applying Multiple Transformations

As briefly mentioned when discussing rotation about multiple axes, sometimes we want to apply multiple transformations to the same point. We can do this by composing transformations. Mathematically this is represented by multiplying the respective matrices in the order that the transformations are applied. If we have two transformations $T_1$ and $T_2$ represented by matrices $M_1$ and $M_2$, then $T_2(T_1(v)) = M_2(M_1v)$. Here $T_1$ is applied first, making $M_1$ the innermost matrix that $v$ is multiplied by first.

Due to the associativity of matrix multiplication, we can multiply $M_2$ and $M_1$ first to get one resulting matrix that is the composite of the two transformations, and then multiply that one matrix by any vertex to apply the same sequence of transformations to each.

$$ T_2(T_1(v)) = M_2(M_1v) = (M_2M_1)v = Mv $$

> Note that matrix multiplication is **not commutative** and therefore the order you apply transformations does change the outcome! The product $M_2M_1$ may not be the same as $M_1M_2$. This is particularly the case when translations are involved because scaling and rotation occur relative to the world origin and not the object itself.

One way to prevent this from causing problems in your own code is to use a standardized order in which you apply transformations to maintain consistency. One common method is **TRSv** where first the point is scaled, then rotated, _then_ translated after the first two transformations occur at the origin.

<details>
<summary>How does this change the outcome?</summary>
  
<img src="SRT.gif" />

<img src="TRS.gif" />
  
</details>

**Task 1: Making Individual Transformation Matrices**

Now that we've learned how to create a few basic types of transformation matrices, it's time for you to try filling in a few of them for yourself! Throughout the lab we will be referring to this graph:

**NOTE: Might need to change the values after demo is made**

![](transforms.png)

You might notice this looks a bit like a modified version of the scene graphs discussed in class. We'll take a closer look at understanding the graph structure later in the lab and in the next lab, but for now let's focus on some of the labeled transformations.

<details>
<summary>How to read the transformations</summary>

At the top of the graph is the world origin. From it, the rest of our objects and camera branch off, with nodes in between to represent the transformations applied to the objects and camera.

Here’s a guide to our notation of transformations:

```
S X,Y,Z: scale by factors X, Y, and Z along the corresponding axes
R X,Y,Z,𝜃: rotate by angle 𝜃 about the axis defined by unit vector (X,Y,Z)
T X,Y,Z: translate by X, Y, and Z along the corresponding axes
```

</details>

Using our transformation building blocks to make more complex transformations, we can use any combination of these to place objects in our 3D scene. In practice, when we say "objects" we mean some defined set of points to which we can apply transformations, like the shapes that you will be rendering in your future projects. For now, the demo just visually represents them as a set of axes to indicate the location, orientation, and scale in the world.

In the stencil code for the lab you should find `insertFileNameHere.cpp` with functions `getMatrixA`, `getMatrixB`, and `getMatrixC`. Each of these functions is used by our program to get transformation matrices A, B, and C as they are described in the graph. **Complete the functions using what we learned about scaling, rotation, and translation** so that they return the correct `glm::mat4` matrices.

![](demoplaceholder.png)

**TODO: as demo is developed insert more specific instructions here for viewing**

**NOTE: Idea of demo is to have display of a “scene” with a marked coordinate system for the world and little axes to represent different objects and the camera. By pressing buttons that apply transformations they code, the little “you” indicator will move and be transformed and applying the transformations correctly will move the axes to match the different objects and camera.**

**Task 2: Composing Transformations**

Great! Now we have some basic transformations created.

![](transforms.png)

Looking at our graph again, each leaf of the tree is an object in the scene. Traversing the tree from the object to the root will create a path through all of the transformations applied to that object in the scene. So to transform Object 1 to world space, for example, first apply transformation A then C. The cumulative transformation matrix of an object in the scene, resulting from this ordered multiplication of matrices, is referred to as the object’s **model matrix**.

Using the graph **fill in functions `getObject1Matrix`, `getObject2Matrix`, and `getObject3Matrix` in the stencil code** with the model matrix of each object. For Object 3, note that there is no specified hierarchy in which the multiple transformations are applied so you should consider how to best order them so that the final result is positioned as desired.

> For Objects 1 and 2, you might want to make use of the functions you wrote in task 1. For any new transformation matrices you might need, feel free to make use of glm's built in functions such `glm::scale`, `glm::rotate`, and `glm::translate`.

**TODO: as demo is developed insert more specific instructions here for viewing**

In the last task, you created the transformation matrices that take objects and transform them to different placements in the world. Just like every other object in a scene, we can represent a camera's position and rotation with a transformation matrix.

## 2. Camera View Matrix

A key part of rendering is being able to figure out where points in the world are relative to the camera's view. To do this, we can use a transformation matrix that represents the transformation of the camera to the origin of the world. By applying this transformation to points in the world, we can convert them to coordinates that treat the camera like an origin from which it views everything else. We refer to this matrix that transforms into the camera’s space as the **view matrix**.

**IMAGE: View matrix transformation**

<details>
<summary>Why do we want to do this?</summary>
<b>TODO</b>
</details>

The camera is defined by its position P and two vectors **look** and **up** which indicate the orientation.

We treat the camera as having been translated from the world origin to $P$. This is exactly like the types of translations you worked with in Tasks 1 and 2. However, for our view matrix, we want to take points in the world and apply to them the opposite of the transformation applied to the camera. Therefore, we translate $P$ back to the origin. Remember that to reverse a transformation, we can take the inverse matrix.

$$ M_{translate} = \begin{bmatrix} 1 && 0 && 0 && P_x \\\ 0 && 1 && 0 && P_y \\\ 0 && 0 && 1 && P_z \\\ 0 && 0 && 0 && 1 \end{bmatrix} ^{-1} =
\begin{bmatrix} 1 && 0 && 0 && -P_x \\\ 0 && 1 && 0 && -P_y \\\ 0 && 0 && 1 && -P_z \\\ 0 && 0 && 0 && 1 \end{bmatrix} $$

The rotation of the camera is fixed by the look and up vectors, look being the direction the camera points and up being the vertical direction relative to the camera's view. 

![](camera.png)

**TODO: replace this image. ^^taken from lectures so should probably be replaced in lecture slides as well if confusing**

Recall from the lecture that we can use these to calculate axes $u$, $v$, and $w$ of the camera's coordinate system using the following formulas:

$$ w = \frac{-look}{||look||} $$

$$ v = \frac{up - (up * w)w}{||up - (up * w)w||} $$

$$ u = v \times w $$

For the rotation component of the view matrix, we want to send the $u$, $v$, and $w$ axes to the world's $x$, $y$, and $z$ axes. To send the world basis vectors to $u$, $v$, and $w$, we use them as the columns of the transformation matrix. Once again, we can do the opposite transformation using the inverse of the matrix. In this case that’s the transpose:

$$ M_{rotate} = \begin{bmatrix} u_x && u_y && u_z && 0 \\\ v_x && v_y && v_z && 0 \\\ w_x && w_y && w_z && 0 \\\ 0 && 0 && 0 && 1 \end{bmatrix} $$

Finally, putting the rotation and translation together, we get one matrix for transforming other objects into the camera's coordinate system.

$$M_{rotate}M_{translate}$$

<details>
<summary>Wait, why T then R?</summary>
  
Wondering why our view matrix does translation first and then rotation, even though earlier we said rotation should usually come first?

As with the objects’ model matrices that we looked at previously, the matrix that represents the transformation of the camera in world space is composed of a rotation first then a translation. Since our view matrix is the inverse, we must reverse the order of the multiplication. Recall:

$$(M_1M_2)^{-1} = M_2^{-1} M_1^{-1}$$

</details>

**Task 3: Building the View Matrix**

![](transforms.png)

Fill in `getCameraMatrix` to return the view matrix of the camera using the specifications given in the above graph.

## 3. Coordinate Spaces

In discussing transformations, we've mentioned the idea of transforming between **coordinate spaces**, but what are coordinate spaces? This is an important concept as you work on building your raytracer. You will often find that certain calculations make sense when you work with them in specific coordinate spaces, but when you're dealing with points and vectors in different spaces you need to know how to use transformations to move between them.

Here we'll cover the main coordinate spaces you will need to work with.

### 3.1 World Space

Think of world space as your default overarching coordinate system. Everything else gets placed into the scene relative to the origin and units of the world's coordinate system. World space is arbitrarily defined and acts as a fixed space within which everything else can be defined. In the transformation graph we've been looking at, it is the root that everything else stems from.

### 3.2 Camera Space

Camera space is what you learned about in part 2 of this lab. It is the coordinate system defined by the camera's position and rotation. In camera space, everything else in the world is relative to the camera's view, with the camera being placed at the origin, and its $uvw$ axes becoming the $xyz$. In part 2, we went over how to get the view  matrix, which takes world space points and transforms them into camera space.

### 3.3 Object Space

Object space is pretty much what it sounds like - the coordinate system defined by a specific object. In the demo, these are represented by the little sets of axes drawn for each object in the scene.

Why do we need coordinates specific to each object? For example, you might want to make a bunch of variations of a sphere that are all different sizes and in different locations. Rather than define each sphere separately, we can define a single sphere as a set of points around an origin, and then transform those points. You can perform calculations on points in the sphere relative to its own central origin, and then use its transformation matrix to get those points in world space.

In task 2 of this lab you have already found some such transformation matrices for objects in the given graph. These take points from the object and transform them into positions in world space. Knowing this, can you think of a way to take a point from a transformed object in world space and find its position in the object's coordinate space?

### 3.4 Relating All Three

That was a lot of information! Here’s a simpler graphic that helps to sum up the relationships between everything we covered in this lab:

![](spaces.png)

The arrows indicate the direction of transformation that the labeled matrix provides. An object’s model matrix will convert from that object’s space to world space. The view matrix will convert from world space to camera space. The inverses of these matrices provide the transformation of the opposite direction of the arrows, going from camera space to world space or world space to object space.

**Task 4: Moving From Camera Space to Object Space**

Now that we have programmed all of the matrices in our graph, we want to make sure that we can actually traverse the graph and find how points are related across different spaces. If the camera sees a point on a cube, we want to be able to take that point (relative to camera space) and find its position relative to world space or object space.

![](transforms.png)

Using the functions you've completed in tasks 1-3 and the graph above, fill in the function `cameraToObj1` so that it returns a matrix that takes points in camera space and transforms them into Object 1's coordinate space, using the matrices that you’ve constructed during previous tasks. 

<details>
<summary>Hint!</summary>
  
Remember that we don't need to go directly from the camera to the object. There might be an intermediate step here that allows us to use multiple transformations we've already worked with...
  
</details>

**Task 5: Moving From Object Space to Camera Space**

Now we want to do the reverse. Fill in `obj2ToCamera` to return a matrix that takes points in Object 2's space and finds them in the camera's space. 

<details>
<summary>Hint!</summary>
  
Think about what we do to a transformation matrix to reverse a transformation. `glm::inverse` might help with this one.
  
</details>

**Task 6: Performing Calculations Across Spaces**

**TODO: Another task with something like providing points in two different spaces and asking students to find the distance between the two in world space.**
