#pragma once
#include "Spells.h"
#include "Items.h"
#include "Extensions.h"
#include "Ultilogic.h"


inline void Sexy()
{
	auto Enemy = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, 1500);
	if (Enemy == nullptr || Enemy->IsDead()) return;
	GGame->IssueOrder(myHero, kAttackUnit, GGame->CursorPosition());
	GOrbwalking->Orbwalk(Enemy, GGame->CursorPosition());
	if (Ignite != nullptr)
	{
		if (UseIgnitecombo->Enabled() && Ignite->IsReady())
		{
			if (Enemy != nullptr && Enemy->IsValidTarget(myHero, 570))
			{
				Ignite->CastOnUnit(Enemy);
			}
		}
	}
	if (use_Youmuu())
	{
		_Youmuu(Enemy);
	}
	if (Flash != nullptr && UseFlash->Enabled() && GetDistance(myHero, Enemy) > 610)
	{
		if (myHero->IsValidTarget(Enemy, R2->Range() - 50))
		{
			if (R2->IsReady() && isR2() && myHero->IsValidTarget(Enemy, R2->Range()))
			{
				if (Enemy != nullptr && !Enemy->IsDead())
				{
					R2->CastOnTarget(Enemy, kHitChanceHigh);
				}
			}
			if (E->IsReady())
			{
				GPluginSDK->DelayFunctionCall(1, []()
				{
					auto Enemy = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, 900);
					if (Enemy != nullptr && !Enemy->IsDead())
					{
						E->CastOnPosition(Enemy->GetPosition());
					}
				});
			}

			if (Flash->IsReady() && UseFlash->Enabled() && GetDistance(myHero, Enemy) > E->Range() + 100)
			{
				GPluginSDK->DelayFunctionCall(4, []()
				{
					auto Enemy = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, 900);
					if (Enemy != nullptr && !Enemy->IsDead())
					{
						Flash->CastOnPosition(Enemy->GetPosition());
					}
				});
			}
			if (W->IsReady())
			{
				if (myHero->IsValidTarget(Enemy, W->Range()))
				{
					GPluginSDK->DelayFunctionCall(10, []()
					{
						W->CastOnPlayer();
					});
				}
			}
			if (Q->IsReady())
			{
				if (myHero->IsValidTarget(Enemy, Q->Range()))
				{
					GPluginSDK->DelayFunctionCall(20, []()
					{
						auto Enemy = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, 900);
						if (Enemy != nullptr && !Enemy->IsDead())
						{
							ModeQ(Enemy);
						}
					});
				}
			}
			GPluginSDK->DelayFunctionCall(30, []()
			{
				auto Enemy = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, 900);
				if (haveitems())
				{
					if (Enemy != nullptr && !Enemy->IsDead())
					{
						UseItems(Enemy);
					}
				}
			});
		}
	}
	else if (!UseFlash->Enabled() || !Flash->IsReady() || GetDistance(myHero, Enemy) < 600)
	{
		if (myHero->IsValidTarget(Enemy, 600))
		{
			if (R2->IsReady() && isR2() && myHero->IsValidTarget(Enemy, R2->Range()))
			{
				if (Enemy != nullptr && !Enemy->IsDead())
				{
					R2->CastOnTarget(Enemy, kHitChanceHigh);
				}
			}
			if (E->IsReady())
			{
				GPluginSDK->DelayFunctionCall(1, []()
				{
					auto Enemy = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, 900);
					if (Enemy != nullptr && !Enemy->IsDead())
					{
						E->CastOnPosition(Enemy->GetPosition());
					}
				});
			}
			if (W->IsReady())
			{
				if (myHero->IsValidTarget(Enemy, W->Range()))
				{
					GPluginSDK->DelayFunctionCall(4, []()
					{
						W->CastOnPlayer();
					});
				}
			}
			if (Q->IsReady())
			{
				if (myHero->IsValidTarget(Enemy, Q->Range()))
				{
					GPluginSDK->DelayFunctionCall(20, []()
					{
						auto Enemy = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, 900);
						if (Enemy != nullptr && !Enemy->IsDead())
						{
							ModeQ(Enemy);
						}
					});
				}
			}
			GPluginSDK->DelayFunctionCall(30, []()
			{
				auto Enemy = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, 900);
				if (haveitems())
				{
					if (Enemy != nullptr && !Enemy->IsDead())
					{
						UseItems(Enemy);
					}
				}
			});
		}
	}
}

static void processSexyBurst(CastedSpell const& spell)
{
	auto Enemy = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, R2->Range());
	if (Enemy != nullptr && !Enemy->IsDead())
	{
		if (spell.Target_ != nullptr && !spell.Target_->IsDead() && spell.Caster_ == myHero)
		{
			if (use_Youmuu())
			{
				_Youmuu(Enemy);
				return;
			}
			if (std::string(spell.Name_) == "ItemTiamatCleave")
			{
				if (W->IsReady() && myHero->IsValidTarget(Enemy, W->Range()))
				{
					W->CastOnPlayer();
				}
				else if (!W->IsReady() && Q->IsReady() && myHero->IsValidTarget(Enemy, 400))
				{
					ModeQ(Enemy);
					AutoAttack = true;
					return;
				}
			}
			if (std::string(spell.Name_) == "RivenFeint") //E spell
			{
				if (W->IsReady() && myHero->IsValidTarget(Enemy, W->Range()))
				{
					W->CastOnPlayer();
					return;
				}
			}
			if (std::string(spell.Name_) == "RivenMartyr") //W spell
			{
				if (Q->IsReady() && myHero->IsValidTarget(Enemy, 400))
				{
					ModeQ(Enemy);
					AutoAttack = true;
					return;
				}
			}
			if (std::string(spell.Name_) == "RivenIzunaBlade")
			{
				if (E->IsReady() && myHero->IsValidTarget(Enemy, R2->Range()))
				{
					E->CastOnPosition(Enemy->ServerPosition());
					return;
				}
				if (W->IsReady() && myHero->IsValidTarget(Enemy, W->Range()))
				{
					W->CastOnPlayer();
					return;
				}
				if (Q->IsReady() && myHero->IsValidTarget(Enemy, 400))
				{
					ModeQ(Enemy);
					AutoAttack = true;
				}
			}
		}
	}
}