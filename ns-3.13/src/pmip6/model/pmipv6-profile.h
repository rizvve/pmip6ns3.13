/* -*-  Mode: C++; c-file-style: "gnu"; indent-tabs-mode:nil; -*- */
/*
 * Proxy Mobile IPv6 (PMIPv6) (RFC5213) Implementation
 *
 * Copyright (c) 2010 KUT, ETRI
 * (Korea Univerity of Technology and Education)
 * (Electronics and Telecommunications Research Institute)
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Author: Hyon-Young Choi <commani@gmail.com>
 */

#ifndef PMIPV6_PROFILE_H
#define PMIPV6_PROFILE_H

#include <stdint.h>

#include <list>

#include "ns3/packet.h"
#include "ns3/nstime.h"
#include "ns3/net-device.h"
#include "ns3/ipv6-address.h"
#include "ns3/ptr.h"
#include "ns3/timer.h"
#include "ns3/sgi-hashmap.h"
#include "ns3/identifier.h"

namespace ns3
{

class Pmipv6Profile : public Object
{
public:

  class Entry;
  
  /**
   * \brief Interface ID
   */
  static TypeId GetTypeId ();

  Pmipv6Profile();
  ~Pmipv6Profile();
  
  Entry *Lookup(Identifier id);
  Entry *Add(Identifier id);
  void Remove(Entry *entry);
  
  void Flush();
  
  class Entry
  {
  public:
    Entry(Pmipv6Profile *pf);
	
    Identifier GetMnIdentifier() const;
	void SetMnIdentifier(Identifier mnId);
	
	Identifier GetMnLinkIdentifier() const;
	void SetMnLinkIdentifier(Identifier mnLinkId);
	
	Ipv6Address GetLmaAddress() const;
	void SetLmaAddress(Ipv6Address lmaa);
	
	std::list<Ipv6Address> GetHomeNetworkPrefixes() const;
	void SetHomeNetworkPrefixes(std::list<Ipv6Address> hnps);
	void AddHomeNetworkPrefix(Ipv6Address hnp);
	
  protected:
  
  private:
    Pmipv6Profile *m_profile;
	
	Identifier m_mnIdentifier;
	Identifier m_mnLinkIdentifier;
	Ipv6Address m_lmaAddress;
	std::list<Ipv6Address> m_homeNetworkPrefixes;
  };
protected:

private:
  typedef sgi::hash_map<Identifier, Pmipv6Profile::Entry *, IdentifierHash> ProfileList;
  typedef sgi::hash_map<Identifier, Pmipv6Profile::Entry *, IdentifierHash>::iterator ProfileListI;
  
  void DoDispose();
  
  ProfileList m_profileList;

};

} /* namespace ns3 */

#endif /* PMIPV6_PROFILE_H */
