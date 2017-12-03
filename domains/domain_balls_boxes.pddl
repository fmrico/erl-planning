(define (domain balls_boxes)

(:requirements :strips :typing :fluents :disjunctive-preconditions :durative-actions)

(:types
	ball
	box
)

(:predicates
	(ball_at_box ?bl - ball ?bx - box)
	(free ?bx - box)
)

(:durative-action move_ball
	:parameters (?b - ball ?from ?to - box)
	:duration ( = ?duration 10)
	:condition (and
		(at start (ball_at_box ?b ?from))
		(over all (free ?to)))
	:effect (and
		(at end (ball_at_box ?b ?to))
		(at end (not (ball_at_box ?b ?from)))
		(at end (free ?from))
		(at end (not (free ?to)))
		))
)
