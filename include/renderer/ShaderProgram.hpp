////////////////////////////////////////////////////////////////////////////////
// guacamole - an interesting scenegraph implementation
//
// Copyright (c) 2011 by Mischa Krempel, Felix Lauer and Simon Schneegans
//
// This program is free software: you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free
// Software Foundation, either version 3 of the License, or (at your option)
// any later version.
//
// This program is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
// FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
// more details.
//
// You should have received a copy of the GNU General Public License along with
// this program.  If not, see <http://www.gnu.org/licenses/>.
//
/// \file
/// \brief A database for accessing material data.
////////////////////////////////////////////////////////////////////////////////

#ifndef SHADERPROGRAM_HPP
#define SHADERPROGRAM_HPP

class VertexShader;
class FragmentShader;

class ShaderProgram {
    public:
        ShaderProgram();
        ShaderProgram( VertexShader const& v_shader, FragmentShader const& f_shader );
        virtual ~ShaderProgram();

        void use() const;

        const static unsigned vertex_location = 0;
        const static unsigned normal_location = 1;

    private:
        unsigned program_id_;
};

#endif // SHADERPROGRAM_HPP
