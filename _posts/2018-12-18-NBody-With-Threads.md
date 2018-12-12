---
layout: post
title: Threading
use_math: true
draft: true
---

This model will extend from our previous example of using TimestepModel to build an extension of MonoBehaviour with a threaded update method called with a calculated timestep.

This time, though, let's build something that will require a great deal more work per step.

The gravitational N-Body problem describes the behaviour of objects in space attracted to each other via gravity. Each object will feel a force of

$$
\vec{F}_i = \sum_j{G \frac{m_i m_j}{r_{ij}^2}  \frac{\vec{r}_{ij}}{r_{ij}}}
$$

where

$$
\vec{r}_{ij} = \vec{r}_j-\vec{r}_i
$$

and

$$
r_{ij} = |\vec{r}_{ij}|
$$

For simplicity, we're going to use a unit system in our simulation such that $G=1$, each mass is equal and $\sum{m_i}=M=1$, and all of our objects start off in a space roughly 1 unit around the origin.
