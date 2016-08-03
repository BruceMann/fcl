/*
 * Software License Agreement (BSD License)
 *
 *  Copyright (c) 2011-2014, Willow Garage, Inc.
 *  Copyright (c) 2014-2016, Open Source Robotics Foundation
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above
 *     copyright notice, this list of conditions and the following
 *     disclaimer in the documentation and/or other materials provided
 *     with the distribution.
 *   * Neither the name of Open Source Robotics Foundation nor the names of its
 *     contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 *  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 *  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 *  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 *  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 */

/** \author Jia Pan */

#ifndef FCL_TRAVERSAL_MESHCOLLISIONTRAVERSALNODE_H
#define FCL_TRAVERSAL_MESHCOLLISIONTRAVERSALNODE_H

#include "fcl/intersect.h"
#include "fcl/traversal/bvh_collision_traversal_node.h"

namespace fcl
{

/// @brief Traversal node for collision between two meshes
template <typename BV>
class MeshCollisionTraversalNode : public BVHCollisionTraversalNode<BV>
{
public:

  using Scalar = typename BV::Scalar;

  MeshCollisionTraversalNode();

  /// @brief Intersection testing between leaves (two triangles)
  void leafTesting(int b1, int b2) const;

  /// @brief Whether the traversal process can stop early
  bool canStop() const;

  Vector3<Scalar>* vertices1;
  Vector3<Scalar>* vertices2;

  Triangle* tri_indices1;
  Triangle* tri_indices2;

  Scalar cost_density;
};

/// @brief Initialize traversal node for collision between two meshes, given the
/// current transforms
template <typename BV>
bool initialize(
    MeshCollisionTraversalNode<BV>& node,
    BVHModel<BV>& model1,
    Transform3<typename BV::Scalar>& tf1,
    BVHModel<BV>& model2,
    Transform3<typename BV::Scalar>& tf2,
    const CollisionRequest<typename BV::Scalar>& request,
    CollisionResult<typename BV::Scalar>& result,
    bool use_refit = false,
    bool refit_bottomup = false);

/// @brief Traversal node for collision between two meshes if their underlying
/// BVH node is oriented node (OBB, RSS, OBBRSS, kIOS)
template <typename Scalar>
class MeshCollisionTraversalNodeOBB : public MeshCollisionTraversalNode<OBB<Scalar>>
{
public:
  MeshCollisionTraversalNodeOBB();

  bool BVTesting(int b1, int b2) const;

  void leafTesting(int b1, int b2) const;

  bool BVTesting(int b1, int b2, const Matrix3<Scalar>& Rc, const Vector3<Scalar>& Tc) const;

  void leafTesting(int b1, int b2, const Matrix3<Scalar>& Rc, const Vector3<Scalar>& Tc) const;

  Matrix3<Scalar> R;
  Vector3<Scalar> T;
};

using MeshCollisionTraversalNodeOBBf = MeshCollisionTraversalNodeOBB<float>;
using MeshCollisionTraversalNodeOBBd = MeshCollisionTraversalNodeOBB<double>;

/// @brief Initialize traversal node for collision between two meshes,
/// specialized for OBB type
template <typename Scalar>
bool initialize(
    MeshCollisionTraversalNodeOBB<Scalar>& node,
    const BVHModel<OBB<Scalar>>& model1,
    const Transform3<Scalar>& tf1,
    const BVHModel<OBB<Scalar>>& model2,
    const Transform3<Scalar>& tf2,
    const CollisionRequest<Scalar>& request,
    CollisionResult<Scalar>& result);

template <typename Scalar>
class MeshCollisionTraversalNodeRSS : public MeshCollisionTraversalNode<RSS<Scalar>>
{
public:
  MeshCollisionTraversalNodeRSS();

  bool BVTesting(int b1, int b2) const;

  void leafTesting(int b1, int b2) const;

  bool BVTesting(int b1, int b2, const Matrix3<Scalar>& Rc, const Vector3<Scalar>& Tc) const;

  void leafTesting(int b1, int b2, const Matrix3<Scalar>& Rc, const Vector3<Scalar>& Tc) const;

  Matrix3<Scalar> R;
  Vector3<Scalar> T;
};

/// @brief Initialize traversal node for collision between two meshes,
/// specialized for RSS type
template <typename Scalar>
bool initialize(
    MeshCollisionTraversalNodeRSS<Scalar>& node,
    const BVHModel<RSS<Scalar>>& model1,
    const Transform3<Scalar>& tf1,
    const BVHModel<RSS<Scalar>>& model2,
    const Transform3<Scalar>& tf2,
    const CollisionRequest<Scalar>& request,
    CollisionResult<Scalar>& result);

template <typename Scalar>
class MeshCollisionTraversalNodekIOS : public MeshCollisionTraversalNode<kIOS<Scalar>>
{
public:
  MeshCollisionTraversalNodekIOS();
 
  bool BVTesting(int b1, int b2) const;

  void leafTesting(int b1, int b2) const;

  Matrix3<Scalar> R;
  Vector3<Scalar> T;
};

/// @brief Initialize traversal node for collision between two meshes,
/// specialized for kIOS type
template <typename Scalar>
bool initialize(
    MeshCollisionTraversalNodekIOS<Scalar>& node,
    const BVHModel<kIOS<Scalar>>& model1,
    const Transform3<Scalar>& tf1,
    const BVHModel<kIOS<Scalar>>& model2,
    const Transform3<Scalar>& tf2,
    const CollisionRequest<Scalar>& request,
    CollisionResult<Scalar>& result);

template <typename Scalar>
class MeshCollisionTraversalNodeOBBRSS : public MeshCollisionTraversalNode<OBBRSS<Scalar>>
{
public:
  MeshCollisionTraversalNodeOBBRSS();
 

  bool BVTesting(int b1, int b2) const;

  void leafTesting(int b1, int b2) const;

  Matrix3<Scalar> R;
  Vector3<Scalar> T;
};

/// @brief Initialize traversal node for collision between two meshes,
/// specialized for OBBRSS type
template <typename Scalar>
bool initialize(
    MeshCollisionTraversalNodeOBBRSS<Scalar>& node,
    const BVHModel<OBBRSS<Scalar>>& model1,
    const Transform3<Scalar>& tf1,
    const BVHModel<OBBRSS<Scalar>>& model2,
    const Transform3<Scalar>& tf2,
    const CollisionRequest<Scalar>& request,
    CollisionResult<Scalar>& result);

namespace details
{

template <typename BV>
void meshCollisionOrientedNodeLeafTesting(
    int b1,
    int b2,
    const BVHModel<BV>* model1,
    const BVHModel<BV>* model2,
    Vector3<typename BV::Scalar>* vertices1,
    Vector3<typename BV::Scalar>* vertices2,
    Triangle* tri_indices1,
    Triangle* tri_indices2,
    const Matrix3<typename BV::Scalar>& R,
    const Vector3<typename BV::Scalar>& T,
    const Transform3<typename BV::Scalar>& tf1,
    const Transform3<typename BV::Scalar>& tf2,
    bool enable_statistics,
    typename BV::Scalar cost_density,
    int& num_leaf_tests,
    const CollisionRequest<typename BV::Scalar>& request,
    CollisionResult<typename BV::Scalar>& result);

} // namespace details

//============================================================================//
//                                                                            //
//                              Implementations                               //
//                                                                            //
//============================================================================//

//==============================================================================
template <typename BV>
MeshCollisionTraversalNode<BV>::MeshCollisionTraversalNode() : BVHCollisionTraversalNode<BV>()
{
  vertices1 = NULL;
  vertices2 = NULL;
  tri_indices1 = NULL;
  tri_indices2 = NULL;
}

//==============================================================================
template <typename BV>
void MeshCollisionTraversalNode<BV>::leafTesting(int b1, int b2) const
{
  if(this->enable_statistics) this->num_leaf_tests++;

  const BVNode<BV>& node1 = this->model1->getBV(b1);
  const BVNode<BV>& node2 = this->model2->getBV(b2);

  int primitive_id1 = node1.primitiveId();
  int primitive_id2 = node2.primitiveId();

  const Triangle& tri_id1 = tri_indices1[primitive_id1];
  const Triangle& tri_id2 = tri_indices2[primitive_id2];

  const Vector3<Scalar>& p1 = vertices1[tri_id1[0]];
  const Vector3<Scalar>& p2 = vertices1[tri_id1[1]];
  const Vector3<Scalar>& p3 = vertices1[tri_id1[2]];
  const Vector3<Scalar>& q1 = vertices2[tri_id2[0]];
  const Vector3<Scalar>& q2 = vertices2[tri_id2[1]];
  const Vector3<Scalar>& q3 = vertices2[tri_id2[2]];

  if(this->model1->isOccupied() && this->model2->isOccupied())
  {
    bool is_intersect = false;

    if(!this->request.enable_contact) // only interested in collision or not
    {
      if(Intersect::intersect_Triangle(p1, p2, p3, q1, q2, q3))
      {
        is_intersect = true;
        if(this->result->numContacts() < this->request.num_max_contacts)
          this->result->addContact(Contact<Scalar>(this->model1, this->model2, primitive_id1, primitive_id2));
      }
    }
    else // need compute the contact information
    {
      Scalar penetration;
      Vector3<Scalar> normal;
      unsigned int n_contacts;
      Vector3<Scalar> contacts[2];

      if(Intersect::intersect_Triangle(p1, p2, p3, q1, q2, q3,
                                       contacts,
                                       &n_contacts,
                                       &penetration,
                                       &normal))
      {
        is_intersect = true;

        if(this->request.num_max_contacts < n_contacts + this->result->numContacts())
          n_contacts = (this->request.num_max_contacts >= this->result->numContacts()) ? (this->request.num_max_contacts - this->result->numContacts()) : 0;

        for(unsigned int i = 0; i < n_contacts; ++i)
        {
          this->result->addContact(Contact<Scalar>(this->model1, this->model2, primitive_id1, primitive_id2, contacts[i], normal, penetration));
        }
      }
    }

    if(is_intersect && this->request.enable_cost)
    {
      AABB<Scalar> overlap_part;
      AABB<Scalar>(p1, p2, p3).overlap(AABB<Scalar>(q1, q2, q3), overlap_part);
      this->result->addCostSource(CostSource<Scalar>(overlap_part, cost_density), this->request.num_max_cost_sources);
    }
  }
  else if((!this->model1->isFree() && !this->model2->isFree()) && this->request.enable_cost)
  {
    if(Intersect::intersect_Triangle(p1, p2, p3, q1, q2, q3))
    {
      AABB<Scalar> overlap_part;
      AABB<Scalar>(p1, p2, p3).overlap(AABB<Scalar>(q1, q2, q3), overlap_part);
      this->result->addCostSource(CostSource<Scalar>(overlap_part, cost_density), this->request.num_max_cost_sources);
    }
  }
}

//==============================================================================
template <typename BV>
bool MeshCollisionTraversalNode<BV>::canStop() const
{
  return this->request.isSatisfied(*(this->result));
}

//==============================================================================
template <typename BV>
bool initialize(
    MeshCollisionTraversalNode<BV>& node,
    BVHModel<BV>& model1,
    Transform3<typename BV::Scalar>& tf1,
    BVHModel<BV>& model2,
    Transform3<typename BV::Scalar>& tf2,
    const CollisionRequest<typename BV::Scalar>& request,
    CollisionResult<typename BV::Scalar>& result,
    bool use_refit,
    bool refit_bottomup)
{
  if(model1.getModelType() != BVH_MODEL_TRIANGLES
     || model2.getModelType() != BVH_MODEL_TRIANGLES)
    return false;

  if(!tf1.matrix().isIdentity())
  {
    std::vector<Vector3d> vertices_transformed1(model1.num_vertices);
    for(int i = 0; i < model1.num_vertices; ++i)
    {
      Vector3d& p = model1.vertices[i];
      Vector3d new_v = tf1 * p;
      vertices_transformed1[i] = new_v;
    }

    model1.beginReplaceModel();
    model1.replaceSubModel(vertices_transformed1);
    model1.endReplaceModel(use_refit, refit_bottomup);

    tf1.setIdentity();
  }

  if(!tf2.matrix().isIdentity())
  {
    std::vector<Vector3d> vertices_transformed2(model2.num_vertices);
    for(int i = 0; i < model2.num_vertices; ++i)
    {
      Vector3d& p = model2.vertices[i];
      Vector3d new_v = tf2 * p;
      vertices_transformed2[i] = new_v;
    }

    model2.beginReplaceModel();
    model2.replaceSubModel(vertices_transformed2);
    model2.endReplaceModel(use_refit, refit_bottomup);

    tf2.setIdentity();
  }

  node.model1 = &model1;
  node.tf1 = tf1;
  node.model2 = &model2;
  node.tf2 = tf2;

  node.vertices1 = model1.vertices;
  node.vertices2 = model2.vertices;

  node.tri_indices1 = model1.tri_indices;
  node.tri_indices2 = model2.tri_indices;

  node.request = request;
  node.result = &result;

  node.cost_density = model1.cost_density * model2.cost_density;

  return true;
}

//==============================================================================
template <typename Scalar>
MeshCollisionTraversalNodeOBB<Scalar>::MeshCollisionTraversalNodeOBB() : MeshCollisionTraversalNode<OBB<Scalar>>()
{
  R.setIdentity();
}

//==============================================================================
template <typename Scalar>
bool MeshCollisionTraversalNodeOBB<Scalar>::BVTesting(int b1, int b2) const
{
  if(this->enable_statistics) this->num_bv_tests++;
  return !overlap(R, T, this->model1->getBV(b1).bv, this->model2->getBV(b2).bv);
}

//==============================================================================
template <typename Scalar>
void MeshCollisionTraversalNodeOBB<Scalar>::leafTesting(int b1, int b2) const
{
  details::meshCollisionOrientedNodeLeafTesting(
        b1,
        b2,
        this->model1,
        this->model2,
        this->vertices1,
        this->vertices2,
        this->tri_indices1,
        this->tri_indices2,
        R,
        T,
        this->tf1,
        this->tf2,
        this->enable_statistics,
        this->cost_density,
        this->num_leaf_tests,
        this->request,
        *this->result);
}

//==============================================================================
template <typename Scalar>
bool MeshCollisionTraversalNodeOBB<Scalar>::BVTesting(
    int b1, int b2, const Matrix3<Scalar>& Rc, const Vector3<Scalar>& Tc) const
{
  if(this->enable_statistics) this->num_bv_tests++;

  return obbDisjoint(
        Rc, Tc,
        this->model1->getBV(b1).bv.extent,
        this->model2->getBV(b2).bv.extent);
}

//==============================================================================
template <typename Scalar>
void MeshCollisionTraversalNodeOBB<Scalar>::leafTesting(
    int b1, int b2, const Matrix3<Scalar>& Rc, const Vector3<Scalar>& Tc) const
{
  details::meshCollisionOrientedNodeLeafTesting(
        b1,
        b2,
        this->model1,
        this->model2,
        this->vertices1,
        this->vertices2,
        this->tri_indices1,
        this->tri_indices2,
        R,
        T,
        this->tf1,
        this->tf2,
        this->enable_statistics,
        this->cost_density,
        this->num_leaf_tests,
        this->request,
        *this->result);
}

//==============================================================================
template <typename Scalar>
MeshCollisionTraversalNodeRSS<Scalar>::MeshCollisionTraversalNodeRSS() : MeshCollisionTraversalNode<RSS<Scalar>>()
{
  R.setIdentity();
}

//==============================================================================
template <typename Scalar>
bool MeshCollisionTraversalNodeRSS<Scalar>::BVTesting(int b1, int b2) const
{
  if(this->enable_statistics) this->num_bv_tests++;

  return !overlap(
        R, T,
        this->model1->getBV(b1).bv,
        this->model2->getBV(b2).bv);
}

//==============================================================================
template <typename Scalar>
void MeshCollisionTraversalNodeRSS<Scalar>::leafTesting(int b1, int b2) const
{
  details::meshCollisionOrientedNodeLeafTesting(
        b1,
        b2,
        this->model1,
        this->model2,
        this->vertices1,
        this->vertices2,
        this->tri_indices1,
        this->tri_indices2,
        R,
        T,
        this->tf1,
        this->tf2,
        this->enable_statistics,
        this->cost_density,
        this->num_leaf_tests,
        this->request,
        *this->result);
}

//==============================================================================
template <typename Scalar>
MeshCollisionTraversalNodekIOS<Scalar>::MeshCollisionTraversalNodekIOS() : MeshCollisionTraversalNode<kIOS<Scalar>>()
{
  R.setIdentity();
}

//==============================================================================
template <typename Scalar>
bool MeshCollisionTraversalNodekIOS<Scalar>::BVTesting(int b1, int b2) const
{
  if(this->enable_statistics) this->num_bv_tests++;

  return !overlap(
        R, T,
        this->model1->getBV(b1).bv,
        this->model2->getBV(b2).bv);
}

//==============================================================================
template <typename Scalar>
void MeshCollisionTraversalNodekIOS<Scalar>::leafTesting(int b1, int b2) const
{
  details::meshCollisionOrientedNodeLeafTesting(
        b1,
        b2,
        this->model1,
        this->model2,
        this->vertices1,
        this->vertices2,
        this->tri_indices1,
        this->tri_indices2,
        R,
        T,
        this->tf1,
        this->tf2,
        this->enable_statistics,
        this->cost_density,
        this->num_leaf_tests,
        this->request,
        *this->result);
}

//==============================================================================
template <typename Scalar>
MeshCollisionTraversalNodeOBBRSS<Scalar>::MeshCollisionTraversalNodeOBBRSS()
  : MeshCollisionTraversalNode<OBBRSS<Scalar>>()
{
  R.setIdentity();
}

//==============================================================================
template <typename Scalar>
bool MeshCollisionTraversalNodeOBBRSS<Scalar>::BVTesting(int b1, int b2) const
{
  if(this->enable_statistics) this->num_bv_tests++;

  return !overlap(
        R, T,
        this->model1->getBV(b1).bv,
        this->model2->getBV(b2).bv);
}

//==============================================================================
template <typename Scalar>
void MeshCollisionTraversalNodeOBBRSS<Scalar>::leafTesting(int b1, int b2) const
{
  details::meshCollisionOrientedNodeLeafTesting(
        b1,
        b2,
        this->model1,
        this->model2,
        this->vertices1,
        this->vertices2,
        this->tri_indices1,
        this->tri_indices2,
        R,
        T,
        this->tf1,
        this->tf2,
        this->enable_statistics,
        this->cost_density,
        this->num_leaf_tests,
        this->request,
        *this->result);
}

namespace details
{

template <typename BV>
void meshCollisionOrientedNodeLeafTesting(
    int b1, int b2,
    const BVHModel<BV>* model1,
    const BVHModel<BV>* model2,
    Vector3<typename BV::Scalar>* vertices1,
    Vector3<typename BV::Scalar>* vertices2,
    Triangle* tri_indices1,
    Triangle* tri_indices2,
    const Matrix3<typename BV::Scalar>& R,
    const Vector3<typename BV::Scalar>& T,
    const Transform3<typename BV::Scalar>& tf1,
    const Transform3<typename BV::Scalar>& tf2,
    bool enable_statistics,
    typename BV::Scalar cost_density,
    int& num_leaf_tests,
    const CollisionRequest<typename BV::Scalar>& request,
    CollisionResult<typename BV::Scalar>& result)
{
  using Scalar = typename BV::Scalar;

  if(enable_statistics) num_leaf_tests++;

  const BVNode<BV>& node1 = model1->getBV(b1);
  const BVNode<BV>& node2 = model2->getBV(b2);

  int primitive_id1 = node1.primitiveId();
  int primitive_id2 = node2.primitiveId();

  const Triangle& tri_id1 = tri_indices1[primitive_id1];
  const Triangle& tri_id2 = tri_indices2[primitive_id2];

  const Vector3<Scalar>& p1 = vertices1[tri_id1[0]];
  const Vector3<Scalar>& p2 = vertices1[tri_id1[1]];
  const Vector3<Scalar>& p3 = vertices1[tri_id1[2]];
  const Vector3<Scalar>& q1 = vertices2[tri_id2[0]];
  const Vector3<Scalar>& q2 = vertices2[tri_id2[1]];
  const Vector3<Scalar>& q3 = vertices2[tri_id2[2]];

  if(model1->isOccupied() && model2->isOccupied())
  {
    bool is_intersect = false;

    if(!request.enable_contact) // only interested in collision or not
    {
      if(Intersect::intersect_Triangle(p1, p2, p3, q1, q2, q3, R, T))
      {
        is_intersect = true;
        if(result.numContacts() < request.num_max_contacts)
          result.addContact(Contact<Scalar>(model1, model2, primitive_id1, primitive_id2));
      }
    }
    else // need compute the contact information
    {
      FCL_REAL penetration;
      Vector3d normal;
      unsigned int n_contacts;
      Vector3d contacts[2];

      if(Intersect::intersect_Triangle(p1, p2, p3, q1, q2, q3,
                                       R, T,
                                       contacts,
                                       &n_contacts,
                                       &penetration,
                                       &normal))
      {
        is_intersect = true;

        if(request.num_max_contacts < result.numContacts() + n_contacts)
          n_contacts = (request.num_max_contacts > result.numContacts()) ? (request.num_max_contacts - result.numContacts()) : 0;

        for(unsigned int i = 0; i < n_contacts; ++i)
        {
          result.addContact(Contact<Scalar>(model1, model2, primitive_id1, primitive_id2, tf1 * contacts[i], tf1.linear() * normal, penetration));
        }
      }
    }

    if(is_intersect && request.enable_cost)
    {
      AABB<Scalar> overlap_part;
      AABB<Scalar>(tf1 * p1, tf1 * p2, tf1 * p3).overlap(AABB<Scalar>(tf2 * q1, tf2 * q2, tf2 * q3), overlap_part);
      result.addCostSource(CostSource<Scalar>(overlap_part, cost_density), request.num_max_cost_sources);
    }
  }
  else if((!model1->isFree() && !model2->isFree()) && request.enable_cost)
  {
    if(Intersect::intersect_Triangle(p1, p2, p3, q1, q2, q3, R, T))
    {
      AABB<Scalar> overlap_part;
      AABB<Scalar>(tf1 * p1, tf1 * p2, tf1 * p3).overlap(AABB<Scalar>(tf2 * q1, tf2 * q2, tf2 * q3), overlap_part);
      result.addCostSource(CostSource<Scalar>(overlap_part, cost_density), request.num_max_cost_sources);
    }
  }
}

} // namespace details

namespace details
{

template<typename BV, typename OrientedNode>
bool setupMeshCollisionOrientedNode(
    OrientedNode& node,
    const BVHModel<BV>& model1, const Transform3<typename BV::Scalar>& tf1,
    const BVHModel<BV>& model2, const Transform3<typename BV::Scalar>& tf2,
    const CollisionRequest<typename BV::Scalar>& request,
    CollisionResult<typename BV::Scalar>& result)
{
  if(model1.getModelType() != BVH_MODEL_TRIANGLES || model2.getModelType() != BVH_MODEL_TRIANGLES)
    return false;

  node.vertices1 = model1.vertices;
  node.vertices2 = model2.vertices;

  node.tri_indices1 = model1.tri_indices;
  node.tri_indices2 = model2.tri_indices;

  node.model1 = &model1;
  node.tf1 = tf1;
  node.model2 = &model2;
  node.tf2 = tf2;

  node.request = request;
  node.result = &result;

  node.cost_density = model1.cost_density * model2.cost_density;

  relativeTransform(tf1, tf2, node.R, node.T);

  return true;
}

} // namespace details

//==============================================================================
template <typename Scalar>
bool initialize(
    MeshCollisionTraversalNodeOBB<Scalar>& node,
    const BVHModel<OBB<Scalar>>& model1,
    const Transform3<Scalar>& tf1,
    const BVHModel<OBB<Scalar>>& model2,
    const Transform3<Scalar>& tf2,
    const CollisionRequest<Scalar>& request,
    CollisionResult<Scalar>& result)
{
  return details::setupMeshCollisionOrientedNode(
        node, model1, tf1, model2, tf2, request, result);
}

//==============================================================================
template <typename Scalar>
bool initialize(
    MeshCollisionTraversalNodeRSS<Scalar>& node,
    const BVHModel<RSS<Scalar>>& model1,
    const Transform3<Scalar>& tf1,
    const BVHModel<RSS<Scalar>>& model2,
    const Transform3<Scalar>& tf2,
    const CollisionRequest<Scalar>& request,
    CollisionResult<Scalar>& result)
{
  return details::setupMeshCollisionOrientedNode(
        node, model1, tf1, model2, tf2, request, result);
}

//==============================================================================
template <typename Scalar>
bool initialize(
    MeshCollisionTraversalNodekIOS<Scalar>& node,
    const BVHModel<kIOS<Scalar>>& model1,
    const Transform3<Scalar>& tf1,
    const BVHModel<kIOS<Scalar>>& model2,
    const Transform3<Scalar>& tf2,
    const CollisionRequest<Scalar>& request,
    CollisionResult<Scalar>& result)
{
  return details::setupMeshCollisionOrientedNode(
        node, model1, tf1, model2, tf2, request, result);
}

//==============================================================================
template <typename Scalar>
bool initialize(
    MeshCollisionTraversalNodeOBBRSS<Scalar>& node,
    const BVHModel<OBBRSS<Scalar>>& model1,
    const Transform3<Scalar>& tf1,
    const BVHModel<OBBRSS<Scalar>>& model2,
    const Transform3<Scalar>& tf2,
    const CollisionRequest<Scalar>& request,
    CollisionResult<Scalar>& result)
{
  return details::setupMeshCollisionOrientedNode(
        node, model1, tf1, model2, tf2, request, result);
}

} // namespace fcl

#endif