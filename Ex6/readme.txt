After creating and testing a 'particle bonker', I continued with developing the
the 1D box of particles with the intention of creating a quasi-experiment to 
measure gamma (ie pV^gamma = const) for a one dimensional, ideal gas. In so doing
I was able to learn about concepts in thermal Physics I had not met yet.

In theory, the ideal gas has the equation of state, relating temperature (T),
pressure(p), volume (V), and number of particles (N),:
		pV = NkT,				(1)
and for adiabatic (Which is the case as the moving wall does work on the gas, but
no heat can enter the gas - heat flow does not even exist in the simulation) 
changes there exists a constant  (y - the heat capacity ratio) such that:
		pV^y = constant.		(2)
Kinetic temperature is defined by the Equipartition Theorem:
		<E> = 0.5*k*T,			(3)
where <E> is the mean kinetic energy (per molecule, per degree of freedom).
Now, we can consider LineWorld (i.e. my box of particles) as having finite area,
and 1 degree of freedom. If we multiply (1) by V^y-1, and then use (2) we obtain:
		TV^y-1 = constant.		(4)
Now dividing (4) by the area, and multiplying 0.5*k*N gives:
		EX^y-1 = constant,		(5)
where E is the total kinetic energy of all the particles, and X is the length
of LineWorld (X = L - v*t, where L is the initial length, v is the speed of 
approach of the right wall to the left, and t is the elapsed time). Finally
taking logs of (5) gives us a way of finding y:
		ln(E) = (1 - y)ln(X) + ln(constant),
thus by finding the gradient we are able to determine y.

The simulation uses classes, for no reason other than to be a learning exercise in
basic OOP for myself (plainer data structures would have been good enough), to represent
the box (LineWorld) and the particles therein (Particle). By using conservation 
of linear momentum, and conservation of (kinetic) energy between the particles, 
we can show that we(in the ideal elastic case in 1D) have, in a manner of speaking, 
conservation of velocity also (v1 + v2 = w1 + w2, the initial and final velocities
of either particle have the same sum). This allows us to use the result in the function.
		The positions of the particles, and the total kinetic energy 
(i.e. system energy) are written to two files.

It is useful to examine a plot of the positions as a function of time in order 
to check for pathological behaviour. Running the simulation for too long 
(when the wall is moving) leads to tunnelling (which is mentioned in the source) 
as a result of the velocities becoming very high. We can only counter this by: 
reducing the wall speed, or the timestep. For the former case, we must also increase 
the number of particles or too few work increments will be done and the gradient 
yielded fraught with error. For the latter case, we must run more steps in the
simulation in order to achieve the same elapsed time as before. Both increase the 
number of calculations by O(n), and both lead to huge amounts of degenerate data, 
not to mention that the simulation will take increasing amounts of real time. 
In the end, by experimenting with various initial conditions, a practical compromise 
was achieved, which is in the presented solution. As such, the write file lines for the 
position data have been commented out, I know that these conditions should not 
result in pathological behaviour. So why waste time writing unused data. 
NB an (empty) position data is still created however.

In order to deal with the large matrices generated, MatLab was used to plot the 
data and perform some linear regression. GNU plot does not seem to cope as easily 
with larger data files, so after using GNU plot, I again decided that MatLab was 
better suited for my program data.

After running the simulation 5 times these data were obtained:
		y|2.9164|3.0807|3.1088|3.0882|3.0922|
		giving,
		y = 3.06 pm 0.04.
		(0.04 is the standard error in the mean to 1 sig fig)
Now this is consistent only to within 1.5 sigma of the theoretical result of
3 (the heat capacity ratio for in ideal gas is related to it's degrees of freedom
by: y = 1 + 2/f). A possible explanation for the this is fact that initial
distribution of the velocities is uniform (which is skewless) while the theory uses
the Boltzmann distribution (which is certainly non uniform, and possess positive 
skew at low mean square speeds. This difference in skew could explain the over
estimation. Increasing the mean square speed would also result in more collisions
per second (reducing quantisation errors as the work increments done by the wall
become smaller and more numerous, ie a better approximation for continuous change). 
In order to better approximate a Boltzmann Distribution, I use a (now commented)
Gaussian distribution and a higher variance in velocities (ie larger c^2 so the
distributions are approximately equal (Boltzmann loses skew as c^2 increases)),
increased the number of particles to 100 (to increase collision number) decreased
the particle radius (r) to 0.00001 (so as to fit them all in and get a better point 
particle approximation) deceased dt to 0.000001 (to prevent tunnelling) and number 
of steps to 4000000 (so the elapsed time would not be very short after decasing dt).
The result was (a lot of waiting, it took about a minute to get the data and plot for each y):
		y|3.0158|2.9759|3.0395|
		giving,
		y = 3.01 pm 0.02.
		Which is more consistent with the theory

NB the presented solution has the original parameters in.

My solution was in a file called Lineworld.cc and in addition I created a file
called EnergyPlot.m containing a MatLab Script to plot data made by LineWorld.