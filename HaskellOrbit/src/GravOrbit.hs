module GravOrbit where

import System.Environment (getArgs)

g :: Double
m :: Double
g = 1
m = 1

data Pos = Pos Double Double deriving (Show,Eq)
data Acc = Acc Double Double deriving (Show,Eq)
type Mass = Double

perpV :: Double -> Mass -> Double -> Double
perpV g' m' r = sqrt(g'*m'/r)

period :: Double -> Mass -> Double -> Double
period g' m' r = 2*pi*sqrt(r*r*r / (g'*m'))


verletStep :: Double -> Acc -> (Pos,Pos) -> (Pos,Pos)
verletStep dt (Acc ax ay) (Pos x0 y0, Pos x1 y1) = (Pos x1 y1, Pos x' y')
  where x' = verletStep1D ax x1 x0 
        y' = verletStep1D ay y1 y0
        verletStep1D a r0 r1 = 2*r1 - r0 + (dt*dt*a)
 
gravForce :: Double -> Mass -> Mass
          -> Pos -> Pos -> Acc
gravForce g' m1 m2 (Pos x2 y2) (Pos x1 y1) = Acc (f*dx) (f*dy)
  where
    f  = g'*m1*m2 / ((x2-x1)**2 + (y2-y1)**2)**(3.0/2)
    dx = x2-x1
    dy = y2-y1

runOrbit :: Double -> Mass -> Mass -> Pos -> Pos -> [Pos]
runOrbit g' m1 m2 p1 p2 = iterate (
