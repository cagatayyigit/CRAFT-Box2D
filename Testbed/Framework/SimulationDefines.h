//
//  SimulationDefines.h
//  Testbed
//
//  Created by Tayfun Ateş on 5.10.2019.
//

#ifndef SimulationDefines_h
#define SimulationDefines_h

#define USE_DEBUG_DRAW 0

#if USE_DEBUG_DRAW
#define BODY b2Body
#define WORLD b2World
#else
#define BODY b2VisBody
#define WORLD b2VisWorld
#endif

#endif /* SimulationDefines_h */
