//
// Copyright (C) 2016 OpenSim Ltd.
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program; if not, see <http://www.gnu.org/licenses/>.
//

package ldmac.inet.visualizer.networknode;

import ldmac.inet.visualizer.base.NetworkNodeVisualizerBase;
import ldmac.inet.visualizer.contract.INetworkNodeVisualizer;

//
// This module visualizes multiple network nodes on a 2D canvas. It maintains a
// NetworkNodeCanvasVisualization figure for each node in the network which can
// be annotated by other visualizers.
//
// @see ~NetworkNodeCanvasVisualizer, ~NetworkNodeVisualizer,
// ~NetworkNodeVisualizerBase, and ~INetworkNodeVisualizer
//
simple NetworkNodeCanvasVisualizer extends NetworkNodeVisualizerBase like INetworkNodeVisualizer
{
    parameters:
        @class(NetworkNodeCanvasVisualizer);
}
