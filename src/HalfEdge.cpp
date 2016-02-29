//
// HalfEdge.cpp
// Mesh_Editor_Xcode
//
// Created by Cristian Troncoso on 2/12/2016
// Copyright @ 2016 Cristian Troncoso. All rights reserved
//

#include "HalfEdge.hpp"


HalfEdge::HalfEdge(Face *f, Vertex *inVer, Vertex *outVer)
{
    face    = f;
    end     = inVer;
    start   = outVer;
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

void HalfEdge::setTwin(HalfEdge * t)
{
    twin = t;
}

void HalfEdge::setEndVertex(Vertex *e)
{
    end = e;
}

void HalfEdge::setStartVertex(Vertex *s)
{
    start = s;
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

Vertex * HalfEdge::getStartVertex()
{
    return start;
}

Vertex * HalfEdge::getEndVertex()
{
    return end;
}

Face * HalfEdge::getFace()
{
    return face;
}



