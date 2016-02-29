//
// HalfEdge.cpp
// Mesh_Editor_Xcode
//
// Created by Camel on 2/12/2016
// Copyright @ 2016 Camel. All rights reserved
//

#include "HalfEdge.hpp"


HalfEdge::HalfEdge(Face *f, Vertex *inVer, Vertex *outVer)
{
    face    = f;
    in      = inVer;
    out     = outVer;
    next    = NULL;
    prev    = NULL;
    twin    = NULL;
}

HalfEdge::~HalfEdge()
{
    delete prev;
    delete next;
    delete twin;
}

void HalfEdge::setNext(HalfEdge * n)
{
    next = n;
}

void HalfEdge::setPrev(HalfEdge * p)
{
    prev = p;
}

void HalfEdge::setTwin(HalfEdge * o)
{
    twin = o;
}

void HalfEdge::setOutVertex(Vertex *o)
{
    out = o;
}

void HalfEdge::setInVertex(Vertex *i)
{
    in = i;
}

void HalfEdge::setFace(Face *f)
{
    face = f;
}

HalfEdge * HalfEdge::getNext()
{
    return next;
}

HalfEdge * HalfEdge::getPrev()
{
    return prev;
}

HalfEdge * HalfEdge::getTwin()
{
    return twin;
}

Vertex * HalfEdge::getInVertex()
{
    return in;
}

Vertex * HalfEdge::getOutVertex()
{
    return out;
}

Face * HalfEdge::getFace()
{
    return face;
}



