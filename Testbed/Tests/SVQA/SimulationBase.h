//
//  SimulationBase.h
//  Testbed
//
//  Created by Tayfun Ateş on 24.11.2019.
//

#ifndef SimulationBase_h
#define SimulationBase_h

#include "Simulation.h"
#include "Settings.h"
#include "SimulationID.h"

namespace svqa {
    #define SET_FILE_OUTPUT_FALSE ((SimulationRenderer*)((b2VisWorld*)m_world)->getRenderer())->setFileOutput(false);
    #define SET_FILE_OUTPUT_TRUE(X) ((SimulationRenderer*)((b2VisWorld*)m_world)->getRenderer())->setFileOutput((X), m_pSettings->bufferWidth, m_pSettings->bufferHeight);
    #define FINISH_SIMULATION {((SimulationRenderer*)((b2VisWorld*)m_world)->getRenderer())->Finish(); exit(0);};

    class SimulationBase : public Simulation
    {
    public:
        typedef std::shared_ptr<SimulationBase> Ptr;
        
        SimulationBase(Settings::Ptr _settings_)
        {
            m_pSettings = _settings_;
            m_nDistinctColorUsed = 8;
        }

        /// A single step of the simulation
        /// Derive simulations must implement this
        virtual void Step(SettingsBase* settings) = 0;
        
        /// Gets the common settings object
        Settings::Ptr getSettings()
        {
            return m_pSettings;
        }
        
        /// Name of the simulation
        /// Derived simulations must have names
        virtual SimulationID getIdentifier() = 0;
        
    protected:
        Settings::Ptr m_pSettings;
        unsigned short m_nDistinctColorUsed;
        
        int randWithBound(const int& bound)
        {
            return (rand() & (RAND_LIMIT)) % bound;
        }
        
        virtual bool isSceneStable()
        {
            b2Body* bodies = m_world->GetBodyList();
            for (b2Body* b = bodies; b; b = b->GetNext())
            {
                if(b->IsAwake() && !(b->GetType() == b2_staticBody)) {
                    return false;
                }
            }
            return true;
        }
    };
}

#endif /* SimulationBase_h */
