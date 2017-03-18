module GravOrbit where

import System.Environment (getArgs)

gConst :: Double
gConst = 1

data Pos = Pos Double Double deriving (Show,Eq)
data Acc = Acc Double Double deriving (Show,Eq)
data Force = Force Double Double deriving (Show,Eq)
type Mass = Double
data DynMass = DynMass { mmass :: Mass, mpos :: Pos
                       , mprevpos :: Pos, mID :: Int} deriving (Show,Eq)

fadd :: Force -> Force -> Force
fadd (Force fx1 fy1) (Force fx2 fy2) = Force (fx1+fx2) (fy1+fy2)
             
mass0 = DynMass {mmass=1, mpos=Pos 0 0, mprevpos=Pos 0 0, mID=0}
mass1 = DynMass {mmass=1, mpos=Pos 9 0, mprevpos=Pos 8.9 0, mID=1}

massEq :: DynMass -> DynMass -> Bool
massEq m1 m2 = mID m1 == mID m2
        
allMasses :: [DynMass]
allMasses = [mass0,mass1]

f2m :: Force -> Mass -> Acc
f2m (Force fx fy) m' = Acc (fx/m') (fy/m')

genForces :: DynMass -> [DynMass] -> [Force]
genForces mass masses = map (mGrav gConst mass) (filter (not . massEq mass) masses)
            
mGrav :: Double -> DynMass -> DynMass -> Force
mGrav g' m1 m2 = gravForce g' (mmass m1) (mmass m2) (mpos m1) (mpos m2)

gravStep :: [DynMass] -> 
                 
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
          -> Pos -> Pos -> Force
gravForce g' m1 m2 (Pos x2 y2) (Pos x1 y1) = Force (f*dx) (f*dy)
  where
    f  = g'*m1*m2 / (dx**2 + dy**2)**(3.0/2)
    dx = x2-x1
    dy = y2-y1
